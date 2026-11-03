#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"
#include "FactoryPresets.h"

//==============================================================================
namespace
{
    juce::NormalisableRange<float> skewed (float lo, float hi, float centre)
    {
        juce::NormalisableRange<float> r (lo, hi);
        r.setSkewForCentre (centre);
        return r;
    }

    // Kształtowanie fali (wywoływane w torze z oversamplingiem)
    inline float shape (float x, int type, float g)
    {
        const float y = x * g;
        switch (type)
        {
            case 1:  return juce::jlimit (-1.0f, 1.0f, y);                                  // hard clip
            case 2:  return std::sin (y * juce::MathConstants<float>::halfPi);               // wavefolder
            default: return std::tanh (y);                                                   // soft (tanh)
        }
    }
}

//==============================================================================
BassoraAudioProcessor::BassoraAudioProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STATE", createLayout())
{
    WavetableBank::get();      // zbuduj tablice teraz, a nie w wątku audio

    auto ptr = [this] (const char* id) { return apvts.getRawParameterValue (id); };

    params.wave      = ptr (IDs::wave);
    params.wtPos     = ptr (IDs::wtPos);
    params.tune      = ptr (IDs::tune);
    params.sub       = ptr (IDs::sub);
    params.click     = ptr (IDs::click);
    params.wave2     = ptr (IDs::wave2);
    params.wtPos2    = ptr (IDs::wtPos2);
    params.semis2    = ptr (IDs::semis2);
    params.detune2   = ptr (IDs::detune2);
    params.level2    = ptr (IDs::level2);
    params.pitchAmt  = ptr (IDs::pitchAmt);
    params.pitchTime = ptr (IDs::pitchTime);
    params.glide     = ptr (IDs::glide);
    params.legato    = ptr (IDs::legato);
    params.lfoShape  = ptr (IDs::lfoShape);
    params.lfoTarget = ptr (IDs::lfoTarget);
    params.lfoSync   = ptr (IDs::lfoSync);
    params.lfoRate   = ptr (IDs::lfoRate);
    params.lfoDepth  = ptr (IDs::lfoDepth);
    params.attack    = ptr (IDs::attack);
    params.decay     = ptr (IDs::decay);
    params.sustain   = ptr (IDs::sustain);
    params.release   = ptr (IDs::release);
    params.driveType = ptr (IDs::driveType);
    params.drive     = ptr (IDs::drive);
    params.cutoff    = ptr (IDs::cutoff);
    params.reso      = ptr (IDs::reso);
    params.gain      = ptr (IDs::gain);
    params.macro1    = ptr (IDs::macro1);
    params.macro2    = ptr (IDs::macro2);
    params.macro3    = ptr (IDs::macro3);
    params.macro4    = ptr (IDs::macro4);
    params.eqOn      = ptr (IDs::eqOn);
    params.eqLoF     = ptr (IDs::eqLoF);
    params.eqLoG     = ptr (IDs::eqLoG);
    params.eqMidF    = ptr (IDs::eqMidF);
    params.eqMidG    = ptr (IDs::eqMidG);
    params.eqMidQ    = ptr (IDs::eqMidQ);
    params.eqHiF     = ptr (IDs::eqHiF);
    params.eqHiG     = ptr (IDs::eqHiG);
    params.compOn      = ptr (IDs::compOn);
    params.compThresh  = ptr (IDs::compThresh);
    params.compRatio   = ptr (IDs::compRatio);
    params.compAttack  = ptr (IDs::compAttack);
    params.compRelease = ptr (IDs::compRelease);
    params.compMakeup  = ptr (IDs::compMakeup);
    params.compMix     = ptr (IDs::compMix);

    lfoBuf.assign (4096, 0.0f);
    refreshPresetList();
}

juce::AudioProcessorValueTreeState::ParameterLayout BassoraAudioProcessor::createLayout()
{
    using namespace juce;
    using Attr = AudioParameterFloatAttributes;

    AudioProcessorValueTreeState::ParameterLayout layout;

    auto addFloat = [&layout] (const char* id, const char* name, NormalisableRange<float> range,
                               float def, const char* unit = "")
    {
        layout.add (std::make_unique<AudioParameterFloat> (ParameterID { id, 1 }, name, range, def,
                                                           Attr().withLabel (unit)));
    };

    auto addChoice = [&layout] (const char* id, const char* name, const StringArray& items, int def)
    {
        layout.add (std::make_unique<AudioParameterChoice> (ParameterID { id, 1 }, name, items, def));
    };

    auto addBool = [&layout] (const char* id, const char* name, bool def)
    {
        layout.add (std::make_unique<AudioParameterBool> (ParameterID { id, 1 }, name, def));
    };

    // Oscylator 1
    addChoice (IDs::wave, "Waveform", Choices::waveNames(), 0);
    addFloat (IDs::wtPos, "Morph",  { 0.0f, 1.0f, 0.001f },   0.0f);
    addFloat (IDs::tune,  "Tune",  { -12.0f, 12.0f, 0.01f }, 0.0f, " st");
    addFloat (IDs::sub,   "Sub",   { 0.0f, 1.0f, 0.001f },   0.6f);
    addFloat (IDs::click, "Click", { 0.0f, 1.0f, 0.001f },   0.25f);

    // Oscylator 2
    addChoice (IDs::wave2, "Osc2 Waveform", Choices::waveNames(), 2);
    addFloat (IDs::wtPos2,  "Osc2 Morph",  { 0.0f, 1.0f, 0.001f },    0.0f);
    addFloat (IDs::semis2,  "Osc2 Tune",   { -24.0f, 24.0f, 1.0f },    0.0f,  " st");
    addFloat (IDs::detune2, "Osc2 Detune", { -100.0f, 100.0f, 0.1f },  10.0f, " ct");
    addFloat (IDs::level2,  "Osc2 Level",  { 0.0f, 1.0f, 0.001f },     0.0f);

    // Pitch / glide
    addFloat (IDs::pitchAmt,  "Pitch Env",  { 0.0f, 48.0f, 0.1f },         12.0f, " st");
    addFloat (IDs::pitchTime, "Pitch Time", skewed (5.0f, 500.0f, 60.0f),   60.0f, " ms");
    addFloat (IDs::glide,     "Glide",      skewed (0.0f, 1000.0f, 120.0f), 0.0f,  " ms");
    addBool  (IDs::legato, "Legato", false);

    // LFO
    addChoice (IDs::lfoShape,  "LFO Shape",  Choices::lfoShapeNames(),  0);
    addChoice (IDs::lfoTarget, "LFO Target", Choices::lfoTargetNames(), 1);
    addChoice (IDs::lfoSync,   "LFO Sync",   Choices::lfoSyncNames(),   0);
    addFloat (IDs::lfoRate,  "LFO Rate",  skewed (0.05f, 30.0f, 3.0f), 2.0f, " Hz");
    addFloat (IDs::lfoDepth, "LFO Depth", { 0.0f, 1.0f, 0.001f },      0.0f);

    // Amp ADSR
    addFloat (IDs::attack,  "Attack",  skewed (0.5f, 500.0f, 20.0f),    1.0f,   " ms");
    addFloat (IDs::decay,   "Decay",   skewed (5.0f, 4000.0f, 600.0f),  900.0f, " ms");
    addFloat (IDs::sustain, "Sustain", { 0.0f, 1.0f, 0.001f },          0.5f);
    addFloat (IDs::release, "Release", skewed (5.0f, 4000.0f, 400.0f),  200.0f, " ms");

    // Drive / filtr / wyjście
    addChoice (IDs::driveType, "Drive Type", StringArray { "Soft", "Hard", "Fold" }, 0);
    addFloat (IDs::drive,  "Drive",  { 0.0f, 1.0f, 0.001f },            0.2f);
    addFloat (IDs::cutoff, "Cutoff", skewed (20.0f, 20000.0f, 1000.0f), 12000.0f, " Hz");
    addFloat (IDs::reso,   "Reso",   { 0.0f, 1.0f, 0.001f },            0.1f);
    addFloat (IDs::gain,   "Gain",   { -24.0f, 6.0f, 0.1f },            -3.0f, " dB");

    // Makra (0 = bez wpływu)
    addFloat (IDs::macro1, "Punch",  { 0.0f, 1.0f, 0.001f }, 0.0f);
    addFloat (IDs::macro2, "Dirt",   { 0.0f, 1.0f, 0.001f }, 0.0f);
    addFloat (IDs::macro3, "Length", { 0.0f, 1.0f, 0.001f }, 0.0f);
    addFloat (IDs::macro4, "Tone",   { 0.0f, 1.0f, 0.001f }, 0.0f);

    // EQ
    addBool  (IDs::eqOn, "EQ On", true);
    addFloat (IDs::eqLoF,  "EQ Low Freq",  skewed (20.0f, 500.0f, 100.0f),     100.0f,  " Hz");
    addFloat (IDs::eqLoG,  "EQ Low Gain",  { -12.0f, 12.0f, 0.1f },            0.0f,    " dB");
    addFloat (IDs::eqMidF, "EQ Mid Freq",  skewed (100.0f, 8000.0f, 800.0f),   800.0f,  " Hz");
    addFloat (IDs::eqMidG, "EQ Mid Gain",  { -12.0f, 12.0f, 0.1f },            0.0f,    " dB");
    addFloat (IDs::eqMidQ, "EQ Mid Q",     skewed (0.2f, 8.0f, 1.0f),          1.0f);
    addFloat (IDs::eqHiF,  "EQ High Freq", skewed (1000.0f, 16000.0f, 5000.0f), 5000.0f, " Hz");
    addFloat (IDs::eqHiG,  "EQ High Gain", { -12.0f, 12.0f, 0.1f },            0.0f,    " dB");

    // Kompresor
    addBool  (IDs::compOn, "Comp On", false);
    addFloat (IDs::compThresh,  "Comp Threshold", { -60.0f, 0.0f, 0.1f },        -18.0f, " dB");
    addFloat (IDs::compRatio,   "Comp Ratio",     skewed (1.0f, 20.0f, 4.0f),     4.0f,  ":1");
    addFloat (IDs::compAttack,  "Comp Attack",    skewed (0.1f, 100.0f, 10.0f),   10.0f, " ms");
    addFloat (IDs::compRelease, "Comp Release",   skewed (10.0f, 1000.0f, 150.0f), 150.0f, " ms");
    addFloat (IDs::compMakeup,  "Comp Makeup",    { 0.0f, 24.0f, 0.1f },          0.0f,  " dB");
    addFloat (IDs::compMix,     "Comp Mix",       { 0.0f, 1.0f, 0.001f },         1.0f);

    return layout;
}

//==============================================================================
bool BassoraAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& out = layouts.getMainOutputChannelSet();
    return out == juce::AudioChannelSet::mono() || out == juce::AudioChannelSet::stereo();
}

void BassoraAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    maxBlock = (size_t) juce::jmax (1, samplesPerBlock);

    voice.prepare (sampleRate);
    updateVoiceParams();

    oversampler.initProcessing (maxBlock);
    oversampler.reset();
    setLatencySamples (juce::roundToInt (oversampler.getLatencyInSamples()));

    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) maxBlock, 1 };
    filter.prepare (spec);
    filter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
    filter.reset();

    cutoffSmoothed.reset (sampleRate, 0.03);
    cutoffSmoothed.setCurrentAndTargetValue (effCutoff);

    lfoSmoothCoeff = 1.0f - std::exp (-1.0f / (0.003f * (float) sampleRate));
    lfoPhase = 0.0;
    lfoSmoothed = 0.0f;
    if (lfoBuf.size() < maxBlock)
        lfoBuf.resize (maxBlock, 0.0f);

    eqLo.reset();  eqMid.reset();  eqHi.reset();
    eqLast.fill (-1.0f);               // wymusza przeliczenie współczynników
    comp.prepare (sampleRate);
    compWasOn = false;
    compGr.store (0.0f);
    updateEffects();

    lastDriveGain = 1.0f + effDrive * 24.0f;
    lastOutGain   = juce::Decibels::decibelsToGain (params.gain->load());
}

void BassoraAudioProcessor::updateVoiceParams()
{
    const float m1 = params.macro1->load();   // PUNCH
    const float m2 = params.macro2->load();   // DIRT
    const float m3 = params.macro3->load();   // LENGTH
    const float m4 = params.macro4->load();   // TONE

    BassVoice::Params p;
    p.wave          = (int) params.wave->load();
    p.wtPos         = params.wtPos->load();
    p.tuneSemis     = params.tune->load();
    p.subLevel      = params.sub->load();
    p.clickAmount   = juce::jlimit (0.0f, 1.0f, params.click->load() + m1 * 0.5f);

    p.wave2         = (int) params.wave2->load();
    p.wtPos2        = params.wtPos2->load();
    p.semis2        = params.semis2->load();
    p.detune2       = params.detune2->load();
    p.level2        = params.level2->load();

    p.pitchEnvSemis = juce::jlimit (0.0f, 48.0f, params.pitchAmt->load() + m1 * 24.0f);
    p.pitchEnvMs    = params.pitchTime->load();
    p.glideMs       = params.glide->load();
    p.legato        = params.legato->load() > 0.5f;

    p.lfoTarget     = (int) params.lfoTarget->load();
    p.lfoDepth      = params.lfoDepth->load();

    const float decayMs   = juce::jlimit (5.0f, 8000.0f, params.decay->load()   * std::exp2 (m3 * 3.0f));
    const float releaseMs = juce::jlimit (5.0f, 8000.0f, params.release->load() * std::exp2 (m3 * 2.0f));
    const float sustain   = juce::jlimit (0.0f, 1.0f,    params.sustain->load() + m3 * 0.3f);

    p.amp = { params.attack->load() * 0.001f, decayMs * 0.001f, sustain, releaseMs * 0.001f };
    voice.setParams (p);

    effDrive  = juce::jlimit (0.0f, 1.0f, params.drive->load() + m2 * 0.7f);
    effCutoff = juce::jlimit (20.0f, 20000.0f, params.cutoff->load() * std::exp2 (m4 * 3.0f));
    effReso   = juce::jlimit (0.0f, 1.0f, params.reso->load() + m4 * 0.25f);
}

void BassoraAudioProcessor::updateEffects()
{
    const std::array<float, 7> now {
        params.eqLoF->load(),  params.eqLoG->load(),
        params.eqMidF->load(), params.eqMidG->load(), params.eqMidQ->load(),
        params.eqHiF->load(),  params.eqHiG->load() };

    if (now != eqLast)
    {
        eqLast = now;
        eqLo.set  (Biquad::Type::lowShelf,  currentSampleRate, now[0], now[1], 0.707);
        eqMid.set (Biquad::Type::peak,      currentSampleRate, now[2], now[3], now[4]);
        eqHi.set  (Biquad::Type::highShelf, currentSampleRate, now[5], now[6], 0.707);
    }

    comp.setParams (params.compThresh->load(), params.compRatio->load(),
                    params.compAttack->load(), params.compRelease->load(),
                    params.compMakeup->load(), params.compMix->load());
}

void BassoraAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;

    const int numSamples  = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    if (numSamples == 0 || numChannels == 0)
        return;

    buffer.clear();
    updateVoiceParams();
    updateEffects();

    if ((size_t) numSamples > lfoBuf.size())
        lfoBuf.resize ((size_t) numSamples, 0.0f);      // normalnie się nie zdarza

    // --- 0) LFO (jedna wartość na próbkę, wygładzona; swobodne albo zsynchronizowane z tempem hosta) ---
    {
        const int shape    = (int) params.lfoShape->load();
        const int syncIdx  = (int) params.lfoSync->load();
        double inc = (double) params.lfoRate->load() / currentSampleRate;

        int numDivs = 0;
        const auto* divs = Choices::syncDivisions (numDivs);

        if (syncIdx > 0 && syncIdx < numDivs)
        {
            double bpm = 120.0, ppq = 0.0;
            bool playing = false, havePpq = false;

            if (auto* ph = getPlayHead())
            {
                if (auto pos = ph->getPosition())
                {
                    if (auto b = pos->getBpm())           bpm = *b;
                    playing = pos->getIsPlaying();
                    if (auto q = pos->getPpqPosition())   { ppq = *q; havePpq = true; }
                }
            }

            bpm = juce::jlimit (20.0, 999.0, bpm);
            const double beats = divs[syncIdx].beats;
            inc = bpm / 60.0 / currentSampleRate / beats;

            if (playing && havePpq)                       // faza trzyma się siatki taktu
            {
                const double cycles = ppq / beats;
                lfoPhase = cycles - std::floor (cycles);
            }
        }

        for (int i = 0; i < numSamples; ++i)
        {
            float raw = 0.0f;
            const float ph = (float) lfoPhase;

            switch (shape)
            {
                case 0:  raw = std::sin (juce::MathConstants<float>::twoPi * ph); break;
                case 1:  raw = 1.0f - 4.0f * std::abs (std::fmod (ph + 0.25f, 1.0f) - 0.5f); break;
                case 2:  raw = 1.0f - 2.0f * ph; break;                  // saw w dół
                case 3:  raw = ph < 0.5f ? 1.0f : -1.0f; break;
                case 4:  raw = lfoHeld; break;                           // sample & hold
                case 5:  raw = 2.0f * ph - 1.0f; break;                  // ramp w górę
                default: raw = lfoPrev + (lfoHeld - lfoPrev) * (ph * ph * (3.0f - 2.0f * ph)); break;   // smooth random
            }

            lfoSmoothed += (raw - lfoSmoothed) * lfoSmoothCoeff;
            lfoBuf[(size_t) i] = lfoSmoothed;

            lfoPhase += inc;
            if (lfoPhase >= 1.0)
            {
                lfoPhase -= std::floor (lfoPhase);
                lfoPrev = lfoHeld;
                lfoHeld = lfoRandom.nextFloat() * 2.0f - 1.0f;
            }
        }
    }

    // --- 1) głos, z dokładnością do próbki względem MIDI ---
    float* mono = buffer.getWritePointer (0);
    int pos = 0;

    for (const auto meta : midi)
    {
        const int evPos = juce::jlimit (pos, numSamples, meta.samplePosition);
        for (int i = pos; i < evPos; ++i)
            mono[i] = voice.getNextSample (lfoBuf[(size_t) i]);
        pos = evPos;

        const auto msg = meta.getMessage();
        if (msg.isNoteOn())                                   voice.noteOn (msg.getNoteNumber(), msg.getFloatVelocity());
        else if (msg.isNoteOff())                             voice.noteOff (msg.getNoteNumber());
        else if (msg.isAllNotesOff() || msg.isAllSoundOff())  voice.allNotesOff();
    }
    for (int i = pos; i < numSamples; ++i)
        mono[i] = voice.getNextSample (lfoBuf[(size_t) i]);

    midi.clear();

    // --- 2) dystorsja z 4x oversamplingiem ---
    const int   lfoTarget = (int) params.lfoTarget->load();
    const float lfoDepth  = params.lfoDepth->load();
    const int   driveType = (int) params.driveType->load();
    const float driveGain = 1.0f + effDrive * 24.0f;
    const float g0 = lastDriveGain;
    lastDriveGain = driveGain;

    juce::dsp::AudioBlock<float> monoBlock (buffer.getArrayOfWritePointers(), 1, (size_t) numSamples);
    const size_t factorI = (size_t) oversampler.getOversamplingFactor();
    const float  factor  = (float) factorI;

    for (size_t start = 0; start < (size_t) numSamples; start += maxBlock)
    {
        const size_t n = std::min (maxBlock, (size_t) numSamples - start);
        auto sub = monoBlock.getSubBlock (start, n);

        auto up = oversampler.processSamplesUp (sub);
        float* d = up.getChannelPointer (0);
        const size_t upN = up.getNumSamples();

        for (size_t j = 0; j < upN; ++j)
        {
            const float frac = ((float) start * factor + (float) j) / ((float) numSamples * factor);
            float g = g0 + (driveGain - g0) * frac;

            if (lfoTarget == 2)
            {
                const float l = lfoBuf[start + j / factorI];
                g = 1.0f + juce::jlimit (0.0f, 1.0f, (g - 1.0f) / 24.0f + l * lfoDepth * 0.5f) * 24.0f;
            }

            d[j] = shape (d[j], driveType, g);
        }

        oversampler.processSamplesDown (sub);
    }

    // --- 3) filtr low-pass (cutoff wygładzony, modulowany LFO co próbkę) ---
    cutoffSmoothed.setTargetValue (effCutoff);
    filter.setResonance (0.707f + effReso * 6.0f);
    const float maxCutoff = (float) (0.45 * currentSampleRate);

    for (int i = 0; i < numSamples; ++i)
    {
        float fc = cutoffSmoothed.getNextValue();
        if (lfoTarget == 1)
            fc *= std::exp2 (lfoBuf[(size_t) i] * lfoDepth * 4.0f);     // +-4 oktawy przy depth = 1

        filter.setCutoffFrequency (juce::jlimit (20.0f, maxCutoff, fc));
        mono[i] = filter.processSample (0, mono[i]);
    }

    // --- 3b) EQ: low shelf + peak + high shelf ---
    if (params.eqOn->load() > 0.5f)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float x = eqLo.process (mono[i]);
            x = eqMid.process (x);
            mono[i] = eqHi.process (x);
        }
    }
    else
    {
        eqLo.reset();  eqMid.reset();  eqHi.reset();
    }

    // --- 3c) kompresor ---
    const bool compOn = params.compOn->load() > 0.5f;
    if (compOn)
    {
        if (! compWasOn)
            comp.reset();

        for (int i = 0; i < numSamples; ++i)
            mono[i] = comp.process (mono[i]);

        compGr.store (comp.takeGainReduction(), std::memory_order_relaxed);
    }
    else
    {
        compGr.store (0.0f, std::memory_order_relaxed);
    }
    compWasOn = compOn;

    // --- 4) gain wyjściowy ---
    const float outGain = juce::Decibels::decibelsToGain (params.gain->load());
    buffer.applyGainRamp (0, 0, numSamples, lastOutGain, outGain);
    lastOutGain = outGain;

    // --- 5) zabezpieczenie 0 dBFS + podgląd do oscyloskopu ---
    int sp = scopePos.load (std::memory_order_relaxed);
    for (int i = 0; i < numSamples; ++i)
    {
        const float y = juce::jlimit (-1.0f, 1.0f, mono[i]);
        mono[i] = y;
        scopeBuf[(size_t) ((sp + i) & (scopeSize - 1))].store (y, std::memory_order_relaxed);
    }
    scopePos.store ((sp + numSamples) & (scopeSize - 1), std::memory_order_relaxed);

    // mono -> pozostałe kanały (bas zostaje w centrum)
    for (int ch = 1; ch < numChannels; ++ch)
        buffer.copyFrom (ch, 0, buffer, 0, 0, numSamples);
}

void BassoraAudioProcessor::getScopeData (float* dest, int n) const
{
    n = juce::jlimit (1, scopeSize, n);
    const int pos = scopePos.load (std::memory_order_relaxed);

    for (int i = 0; i < n; ++i)
        dest[i] = scopeBuf[(size_t) ((pos - n + i + scopeSize) & (scopeSize - 1))].load (std::memory_order_relaxed);
}

//==============================================================================
// Presety
//==============================================================================
int BassoraAudioProcessor::getNumPrograms() { return (int) FactoryPresets::all().size(); }

const juce::String BassoraAudioProcessor::getProgramName (int index)
{
    const auto& presets = FactoryPresets::all();
    return juce::isPositiveAndBelow (index, (int) presets.size()) ? presets[(size_t) index].name : "";
}

void BassoraAudioProcessor::setCurrentProgram (int index)
{
    if (juce::isPositiveAndBelow (index, (int) FactoryPresets::all().size()))
    {
        currentProgram = index;
        loadPreset (index);                 // fabryczne mają te same indeksy na początku listy
    }
}

juce::File BassoraAudioProcessor::getUserPresetDirectory()
{
    return juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory)
               .getChildFile ("BASSORA").getChildFile ("Presets");
}

void BassoraAudioProcessor::refreshPresetList()
{
    presetList.clear();

    for (const auto& p : FactoryPresets::all())
        presetList.push_back ({ p.name, p.category, true, {} });

    auto files = getUserPresetDirectory().findChildFiles (juce::File::findFiles, false, "*.bassorapreset");

    std::vector<PresetInfo> user;
    for (const auto& f : files)
    {
        juce::String name = f.getFileNameWithoutExtension();
        if (auto xml = juce::parseXML (f))
            if (xml->hasTagName ("BassoraPreset") && xml->getStringAttribute ("name").isNotEmpty())
                name = xml->getStringAttribute ("name");
        user.push_back ({ name, "My presets", false, f });
    }

    std::sort (user.begin(), user.end(), [] (const PresetInfo& a, const PresetInfo& b)
               { return a.name.compareIgnoreCase (b.name) < 0; });

    presetList.insert (presetList.end(), user.begin(), user.end());
}

void BassoraAudioProcessor::markCurrentPreset (const juce::String& name, bool user)
{
    apvts.state.setProperty ("presetName", name, nullptr);
    apvts.state.setProperty ("presetUser", user, nullptr);
}

juce::String BassoraAudioProcessor::getCurrentPresetName() const
{
    return apvts.state.getProperty ("presetName", "").toString();
}

int BassoraAudioProcessor::getCurrentPresetIndex() const
{
    const auto name = getCurrentPresetName();
    const bool user = (bool) apvts.state.getProperty ("presetUser", false);

    for (size_t i = 0; i < presetList.size(); ++i)
        if (presetList[i].factory != user && presetList[i].name == name)
            return (int) i;

    return -1;
}

void BassoraAudioProcessor::applyParameterValues (const std::vector<std::pair<juce::String, float>>& values)
{
    for (auto* p : getParameters())
        p->setValueNotifyingHost (p->getDefaultValue());

    for (const auto& [id, value] : values)
        if (auto* p = apvts.getParameter (id))
            p->setValueNotifyingHost (p->convertTo0to1 (value));
}

bool BassoraAudioProcessor::loadPreset (int index)
{
    if (! juce::isPositiveAndBelow (index, (int) presetList.size()))
        return false;

    const auto& info = presetList[(size_t) index];
    std::vector<std::pair<juce::String, float>> values;

    if (info.factory)
    {
        const auto& fp = FactoryPresets::all()[(size_t) index];
        for (int i = 0; i < fp.numValues; ++i)
            values.emplace_back (fp.values[i].id, fp.values[i].value);
    }
    else
    {
        auto xml = juce::parseXML (info.file);
        if (xml == nullptr || ! xml->hasTagName ("BassoraPreset"))
            return false;

        for (auto* e : xml->getChildWithTagNameIterator ("P"))
            values.emplace_back (e->getStringAttribute ("id"), (float) e->getDoubleAttribute ("v"));
    }

    applyParameterValues (values);
    markCurrentPreset (info.name, ! info.factory);
    return true;
}

bool BassoraAudioProcessor::userPresetExists (const juce::String& name) const
{
    return getUserPresetDirectory()
               .getChildFile (juce::File::createLegalFileName (name.trim()) + ".bassorapreset").existsAsFile();
}

bool BassoraAudioProcessor::saveUserPreset (const juce::String& rawName, bool overwrite)
{
    const auto name = rawName.trim();
    if (name.isEmpty())
        return false;

    const auto dir = getUserPresetDirectory();
    if (! dir.createDirectory().wasOk())
        return false;

    const auto file = dir.getChildFile (juce::File::createLegalFileName (name) + ".bassorapreset");
    if (file.existsAsFile() && ! overwrite)
        return false;

    juce::XmlElement xml ("BassoraPreset");
    xml.setAttribute ("name", name);
    xml.setAttribute ("version", 1);

    for (auto* p : getParameters())
    {
        if (auto* rp = dynamic_cast<juce::RangedAudioParameter*> (p))
        {
            auto* e = xml.createNewChildElement ("P");
            e->setAttribute ("id", rp->paramID);
            e->setAttribute ("v", (double) rp->convertFrom0to1 (rp->getValue()));
        }
    }

    if (! xml.writeTo (file))
        return false;

    refreshPresetList();
    markCurrentPreset (name, true);
    return true;
}

bool BassoraAudioProcessor::deleteUserPreset (int index)
{
    if (! juce::isPositiveAndBelow (index, (int) presetList.size()) || presetList[(size_t) index].factory)
        return false;

    const auto file = presetList[(size_t) index].file;
    const bool wasCurrent = (index == getCurrentPresetIndex());

    if (! file.moveToTrash() && ! file.deleteFile())
        return false;

    if (wasCurrent)
        markCurrentPreset ({}, true);

    refreshPresetList();
    return true;
}

//==============================================================================
juce::AudioProcessorEditor* BassoraAudioProcessor::createEditor()
{
    return new BassoraAudioProcessorEditor (*this);
}

void BassoraAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void BassoraAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BassoraAudioProcessor();
}
