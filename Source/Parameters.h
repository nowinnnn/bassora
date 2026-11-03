#pragma once

#include <juce_core/juce_core.h>

// Identyfikatory parametrów BASSORA (APVTS, presety, edytor).
namespace IDs
{
    // Oscylator 1
    inline constexpr const char* wave      = "wave";
    inline constexpr const char* wtPos     = "wtPos";
    inline constexpr const char* tune      = "tune";
    inline constexpr const char* sub       = "sub";
    inline constexpr const char* click     = "click";

    // Oscylator 2
    inline constexpr const char* wave2     = "wave2";
    inline constexpr const char* wtPos2    = "wtPos2";
    inline constexpr const char* semis2    = "semis2";
    inline constexpr const char* detune2   = "detune2";
    inline constexpr const char* level2    = "level2";

    // Pitch / glide
    inline constexpr const char* pitchAmt  = "pitchAmt";
    inline constexpr const char* pitchTime = "pitchTime";
    inline constexpr const char* glide     = "glide";
    inline constexpr const char* legato    = "legato";

    // LFO
    inline constexpr const char* lfoShape  = "lfoShape";
    inline constexpr const char* lfoTarget = "lfoTarget";
    inline constexpr const char* lfoSync   = "lfoSync";
    inline constexpr const char* lfoRate   = "lfoRate";
    inline constexpr const char* lfoDepth  = "lfoDepth";

    // Obwiednia amplitudy
    inline constexpr const char* attack    = "attack";
    inline constexpr const char* decay     = "decay";
    inline constexpr const char* sustain   = "sustain";
    inline constexpr const char* release   = "release";

    // Dystorsja / filtr / wyjście
    inline constexpr const char* driveType = "driveType";
    inline constexpr const char* drive     = "drive";
    inline constexpr const char* cutoff    = "cutoff";
    inline constexpr const char* reso      = "reso";
    inline constexpr const char* gain      = "gain";

    // Makra
    inline constexpr const char* macro1    = "macro1";   // PUNCH
    inline constexpr const char* macro2    = "macro2";   // DIRT
    inline constexpr const char* macro3    = "macro3";   // LENGTH
    inline constexpr const char* macro4    = "macro4";   // TONE

    // EQ (3 pasma)
    inline constexpr const char* eqOn      = "eqOn";
    inline constexpr const char* eqLoF     = "eqLoF";
    inline constexpr const char* eqLoG     = "eqLoG";
    inline constexpr const char* eqMidF    = "eqMidF";
    inline constexpr const char* eqMidG    = "eqMidG";
    inline constexpr const char* eqMidQ    = "eqMidQ";
    inline constexpr const char* eqHiF     = "eqHiF";
    inline constexpr const char* eqHiG     = "eqHiG";

    // Kompresor
    inline constexpr const char* compOn      = "compOn";
    inline constexpr const char* compThresh  = "compThresh";
    inline constexpr const char* compRatio   = "compRatio";
    inline constexpr const char* compAttack  = "compAttack";
    inline constexpr const char* compRelease = "compRelease";
    inline constexpr const char* compMakeup  = "compMakeup";
    inline constexpr const char* compMix     = "compMix";
}

// Listy wyborów współdzielone przez procesor i edytor.
// Nowe pozycje wolno dopisywać tylko na końcu (stare presety i projekty trzymają indeksy).
namespace Choices
{
    // Pierwsze 4 = klasyczne kształty, reszta = tablice z morfingiem (parametr "Morph").
    inline juce::StringArray waveNames()
    {
        return { "Sine", "Triangle", "Saw", "Square",
                 "Morph", "PWM", "Fold", "Harmonics", "Sync", "Vowel", "Phase Dist", "Digital", "FM" };
    }

    inline juce::StringArray lfoShapeNames()  { return { "Sine", "Tri", "Saw", "Square", "S&H", "Ramp", "Smooth" }; }
    inline juce::StringArray lfoTargetNames() { return { "Pitch", "Cutoff", "Drive", "Amp", "Morph" }; }

    // Synchronizacja LFO: nazwa + długość jednego cyklu w ćwierćnutach (0 = swobodne, w Hz).
    struct SyncDivision { const char* name; double beats; };

    inline const SyncDivision* syncDivisions (int& count)
    {
        static const SyncDivision divs[] =
        {
            { "Free",  0.0 },
            { "4 Bar", 16.0 }, { "2 Bar", 8.0 }, { "1 Bar", 4.0 },
            { "1/2",   2.0 },  { "1/4",   1.0 }, { "1/8",   0.5 }, { "1/16",  0.25 }, { "1/32", 0.125 },
            { "1/2T",  4.0 / 3.0 }, { "1/4T", 2.0 / 3.0 }, { "1/8T", 1.0 / 3.0 }, { "1/16T", 1.0 / 6.0 },
            { "1/2D",  3.0 },  { "1/4D",  1.5 }, { "1/8D",  0.75 }, { "1/16D", 0.375 },
        };
        count = (int) (sizeof (divs) / sizeof (divs[0]));
        return divs;
    }

    inline juce::StringArray lfoSyncNames()
    {
        int n = 0;
        const auto* d = syncDivisions (n);
        juce::StringArray names;
        for (int i = 0; i < n; ++i)
            names.add (d[i].name);
        return names;
    }
}
