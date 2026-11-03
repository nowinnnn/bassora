#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <atomic>
#include <vector>
#include "BassVoice.h"
#include "Dsp.h"

class BassoraAudioProcessor : public juce::AudioProcessor
{
public:
    BassoraAudioProcessor();
    ~BassoraAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "BASSORA"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 8.0; }

    // Programy widoczne dla hosta = tylko presety fabryczne (stała liczba).
    int getNumPrograms() override;
    int getCurrentProgram() override { return currentProgram; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /** Kopiuje ostatnie n próbek wyjścia (do oscyloskopu w edytorze). n <= scopeSize. */
    void getScopeData (float* dest, int n) const;

    /** Aktualna redukcja głośności kompresora w dB (<= 0), do miernika w edytorze. */
    float getCompGainReduction() const { return compGr.load (std::memory_order_relaxed); }
    double getSampleRateForDisplay() const { return currentSampleRate; }

    static constexpr int scopeSize = 4096;      // potęga dwójki

    //==========================================================================
    // Presety: fabryczne + własne (pliki .bassorapreset w folderze użytkownika)
    struct PresetInfo
    {
        juce::String name;
        juce::String category;
        bool factory = true;
        juce::File file;            // tylko dla własnych
    };

    static juce::File getUserPresetDirectory();

    void refreshPresetList();                                   // wątek GUI
    const std::vector<PresetInfo>& getPresetList() const { return presetList; }
    int  getCurrentPresetIndex() const;                         // -1 = brak / zmieniony
    juce::String getCurrentPresetName() const;
    bool loadPreset (int index);
    bool saveUserPreset (const juce::String& name, bool overwrite);   // false = plik istnieje (gdy !overwrite) lub błąd
    bool userPresetExists (const juce::String& name) const;
    bool deleteUserPreset (int index);

    juce::AudioProcessorValueTreeState apvts;

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void updateVoiceParams();
    void updateEffects();
    void applyParameterValues (const std::vector<std::pair<juce::String, float>>& values);
    void markCurrentPreset (const juce::String& name, bool user);

    struct ParamPtrs
    {
        std::atomic<float> *wave, *wtPos, *tune, *sub, *click;
        std::atomic<float> *wave2, *wtPos2, *semis2, *detune2, *level2;
        std::atomic<float> *pitchAmt, *pitchTime, *glide, *legato;
        std::atomic<float> *lfoShape, *lfoTarget, *lfoSync, *lfoRate, *lfoDepth;
        std::atomic<float> *attack, *decay, *sustain, *release;
        std::atomic<float> *driveType, *drive, *cutoff, *reso, *gain;
        std::atomic<float> *macro1, *macro2, *macro3, *macro4;
        std::atomic<float> *eqOn, *eqLoF, *eqLoG, *eqMidF, *eqMidG, *eqMidQ, *eqHiF, *eqHiG;
        std::atomic<float> *compOn, *compThresh, *compRatio, *compAttack, *compRelease, *compMakeup, *compMix;
    } params {};

    BassVoice voice;

    // 4x oversampling (2^2) dla dystorsji, 1 kanał (tor mono)
    juce::dsp::Oversampling<float> oversampler { 1, 2,
        juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, true, false };

    juce::dsp::StateVariableTPTFilter<float> filter;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> cutoffSmoothed;

    // wartości efektywne (parametr + makra)
    float effDrive = 0.2f, effCutoff = 12000.0f, effReso = 0.1f;

    // LFO
    std::vector<float> lfoBuf;
    double lfoPhase = 0.0;
    float lfoHeld = 0.0f, lfoPrev = 0.0f, lfoSmoothed = 0.0f, lfoSmoothCoeff = 0.01f;
    juce::Random lfoRandom;

    // efekty końcowe
    Biquad eqLo, eqMid, eqHi;
    std::array<float, 7> eqLast { { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f } };
    Compressor comp;
    bool compWasOn = false;
    std::atomic<float> compGr { 0.0f };

    // oscyloskop
    std::array<std::atomic<float>, scopeSize> scopeBuf {};
    std::atomic<int> scopePos { 0 };

    size_t maxBlock = 512;
    float lastDriveGain = 1.0f;
    float lastOutGain = 1.0f;
    double currentSampleRate = 44100.0;
    int currentProgram = 0;

    std::vector<PresetInfo> presetList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassoraAudioProcessor)
};
