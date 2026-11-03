#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include "Dsp.h"
#include <algorithm>
#include <cmath>
#include <vector>

/**
    Monofoniczny głos basowy BASSORA:
    OSC1 + OSC2 (detune) + sub + click, pitch envelope, glide, ADSR.
    LFO jest liczone w procesorze i podawane do głosu (cele: pitch i amp).
*/
class BassVoice
{
public:
    struct Params
    {
        // OSC1
        int   wave          = 0;      // indeks banku wavetable (patrz Choices::waveNames)
        float wtPos         = 0.0f;   // pozycja morfingu 0..1
        float tuneSemis     = 0.0f;
        float subLevel      = 0.6f;
        float clickAmount   = 0.25f;

        // OSC2
        int   wave2         = 2;
        float wtPos2        = 0.0f;
        float semis2        = 0.0f;
        float detune2       = 10.0f;  // cents
        float level2        = 0.0f;

        // pitch env / glide
        float pitchEnvSemis = 12.0f;
        float pitchEnvMs    = 60.0f;
        float glideMs       = 0.0f;
        bool  legato        = false;

        // LFO (cele obsługiwane w głosie: 0 = pitch, 3 = amp, 4 = morph)
        int   lfoTarget     = 1;
        float lfoDepth      = 0.0f;

        juce::ADSR::Parameters amp { 0.001f, 0.9f, 0.5f, 0.2f };
    };

    void prepare (double newSampleRate)
    {
        sampleRate = newSampleRate;
        bank = &WavetableBank::get();
        wtSmoothCoeff = 1.0f - std::exp (-1.0f / (0.005f * (float) sampleRate));
        adsr.setSampleRate (sampleRate);
        clickCoeff = std::exp (-1.0f / (0.004f * (float) sampleRate));
        reset();
        setParams (params);
    }

    void reset()
    {
        adsr.reset();
        heldNotes.clear();
        phase = phase2 = subPhase = 0.0;
        pitchEnv = 0.0f;
        clickEnv = 0.0f;
        wtSmooth1 = params.wtPos;
        wtSmooth2 = params.wtPos2;
    }

    void setParams (const Params& newParams)
    {
        params = newParams;
        adsr.setParameters (params.amp);

        pitchEnvCoeff = std::exp (-1.0f / (juce::jmax (1.0f, params.pitchEnvMs) * 0.001f * (float) sampleRate));
        glideCoeff    = params.glideMs < 0.5f
                          ? 0.0f
                          : std::exp (-1.0f / (params.glideMs * 0.001f * (float) sampleRate));
    }

    void noteOn (int midiNote, float velocity)
    {
        heldNotes.erase (std::remove (heldNotes.begin(), heldNotes.end(), midiNote), heldNotes.end());
        heldNotes.push_back (midiNote);

        const bool wasActive = adsr.isActive();

        targetNote = (float) midiNote;
        vel = velocity;

        if (! wasActive)
            currentNote = targetNote;          // brak glide z ciszy

        if (! wasActive || ! params.legato)
            retrigger (! wasActive);
    }

    void noteOff (int midiNote)
    {
        heldNotes.erase (std::remove (heldNotes.begin(), heldNotes.end(), midiNote), heldNotes.end());

        if (heldNotes.empty())
            adsr.noteOff();
        else
            targetNote = (float) heldNotes.back();   // wraca do wcześniej trzymanej nuty
    }

    void allNotesOff()
    {
        heldNotes.clear();
        adsr.noteOff();
    }

    bool isActive() const { return adsr.isActive(); }

    /** lfo: wartość LFO w zakresie -1..1 */
    float getNextSample (float lfo)
    {
        if (! adsr.isActive())
            return 0.0f;

        // glide w dziedzinie półtonów (wykładniczy)
        currentNote = targetNote + (currentNote - targetNote) * glideCoeff;

        float semis = currentNote - 69.0f + params.tuneSemis + params.pitchEnvSemis * pitchEnv;
        if (params.lfoTarget == 0)
            semis += lfo * params.lfoDepth * 7.0f;
        pitchEnv *= pitchEnvCoeff;

        const double freq = 440.0 * std::exp2 ((double) semis / 12.0);
        const double dt   = juce::jmin (freq / sampleRate, 0.45);

        // pozycje morfingu (wygładzone, żeby ruch gałki nie klikał) + modulacja LFO
        float wtTarget1 = params.wtPos, wtTarget2 = params.wtPos2;
        if (params.lfoTarget == 4)
        {
            const float m = lfo * params.lfoDepth * 0.5f;
            wtTarget1 += m;
            wtTarget2 += m;
        }
        wtSmooth1 += (juce::jlimit (0.0f, 1.0f, wtTarget1) - wtSmooth1) * wtSmoothCoeff;
        wtSmooth2 += (juce::jlimit (0.0f, 1.0f, wtTarget2) - wtSmooth2) * wtSmoothCoeff;

        // OSC1
        float osc = oscSample (params.wave, wtSmooth1, (float) phase, dt);
        phase += dt;
        if (phase >= 1.0) phase -= 1.0;

        // OSC2 (faza biegnie zawsze, żeby nie skakała przy zmianie levelu)
        const double freq2 = freq * std::exp2 ((double) (params.semis2 + params.detune2 * 0.01f) / 12.0);
        const double dt2   = juce::jmin (freq2 / sampleRate, 0.45);
        float osc2 = 0.0f;
        if (params.level2 > 0.0001f)
            osc2 = oscSample (params.wave2, wtSmooth2, (float) phase2, dt2);
        phase2 += dt2;
        if (phase2 >= 1.0) phase2 -= 1.0;

        const float oscMix = (osc + params.level2 * osc2) / (1.0f + params.level2 * 0.7f);

        // sub: sinus oktawę niżej
        const float sub = std::sin (juce::MathConstants<float>::twoPi * (float) subPhase);
        subPhase += dt * 0.5;
        if (subPhase >= 1.0) subPhase -= 1.0;

        // click: krótki impuls szumu
        const float noise = (random.nextFloat() * 2.0f - 1.0f) * clickEnv;
        clickEnv *= clickCoeff;

        const float out = 0.8f * oscMix + params.subLevel * sub + 0.5f * params.clickAmount * noise;

        // LFO -> amp (tremolo)
        float ampMod = 1.0f;
        if (params.lfoTarget == 3)
            ampMod = 1.0f - params.lfoDepth * (0.5f - 0.5f * lfo);

        return out * adsr.getNextSample() * vel * ampMod;
    }

private:
    float oscSample (int wave, float pos, float t, double dt) const
    {
        const auto& table = bank->table (wave);
        return WavetableBank::read (table, WavetableBank::levelForIncrement (dt), pos, t);
    }

    void retrigger (bool resetPhase)
    {
        if (resetPhase)
        {
            phase = 0.0;
            phase2 = 0.0;
            subPhase = 0.0;
        }
        pitchEnv = 1.0f;
        clickEnv = 1.0f;
        adsr.noteOn();
    }

    Params params;
    juce::ADSR adsr;
    juce::Random random;
    std::vector<int> heldNotes;

    const WavetableBank* bank = nullptr;
    float wtSmooth1 = 0.0f, wtSmooth2 = 0.0f, wtSmoothCoeff = 0.01f;

    double sampleRate = 44100.0;
    double phase = 0.0, phase2 = 0.0, subPhase = 0.0;

    float targetNote = 36.0f, currentNote = 36.0f;
    float vel = 1.0f;
    float pitchEnv = 0.0f, pitchEnvCoeff = 0.999f;
    float clickEnv = 0.0f, clickCoeff = 0.99f;
    float glideCoeff = 0.0f;
};
