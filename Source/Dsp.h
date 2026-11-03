#pragma once

#include <juce_core/juce_core.h>
#include <algorithm>
#include <cmath>
#include <complex>
#include <functional>
#include <vector>

//==============================================================================
/**
    Banki fal (wavetable). Każdy bank ma 1 lub 8 ramek (morfing parametrem "Morph").
    Każda ramka jest zapisana w 10 wersjach ograniczonych pasmowo (mipmapy po oktawach),
    więc odczyt z tablicy nie robi aliasingu przy żadnej wysokości dźwięku.
    Tablice buduje się raz (przy pierwszym użyciu), współdzielone przez wszystkie instancje.
*/
class WavetableBank
{
public:
    static constexpr int tableSize = 2048;
    static constexpr int numLevels = 10;        // poziom l zawiera harmoniczne <= (tableSize/2) >> l
    static constexpr int stride    = tableSize + 1;   // +1 próbka (guard) do interpolacji

    struct Table
    {
        int numFrames = 1;
        std::vector<float> data;                // [ramka][poziom][stride]

        const float* get (int frame, int level) const
        {
            return data.data() + ((size_t) frame * numLevels + (size_t) level) * stride;
        }
    };

    static const WavetableBank& get()
    {
        static const WavetableBank instance;
        return instance;
    }

    int numTables() const                       { return (int) tables.size(); }
    const Table& table (int i) const            { return tables[(size_t) juce::jlimit (0, numTables() - 1, i)]; }

    /** Poziom mipmapy dla przyrostu fazy dt (cykle na próbkę). */
    static int levelForIncrement (double dt)
    {
        int e = 0;
        std::frexp (2048.0 * dt, &e);
        return juce::jlimit (0, numLevels - 1, e);
    }

    /** Odczyt z interpolacją liniową (próbka) i liniowym morfingiem między ramkami. pos: 0..1 */
    static float read (const Table& t, int level, float pos, float phase)
    {
        const float fx = phase * (float) tableSize;
        const int   i0 = juce::jlimit (0, tableSize - 1, (int) fx);
        const float fr = fx - (float) i0;

        auto sample = [&] (int frame)
        {
            const float* d = t.get (frame, level);
            return d[i0] + (d[i0 + 1] - d[i0]) * fr;
        };

        if (t.numFrames <= 1)
            return sample (0);

        const float fp = juce::jlimit (0.0f, 1.0f, pos) * (float) (t.numFrames - 1);
        const int   f0 = juce::jmin ((int) fp, t.numFrames - 2);
        const float ff = fp - (float) f0;
        const float a  = sample (f0);
        return a + (sample (f0 + 1) - a) * ff;
    }

private:
    using Shape = std::function<double (double /*t 0..1*/, double /*morph 0..1*/)>;

    WavetableBank()
    {
        constexpr double twoPi = 6.283185307179586;
        constexpr int nFrames = 8;

        auto sine = [=] (double t) { return std::sin (twoPi * t); };
        auto tri  = [] (double t)
        {
            double tp = t + 0.25;
            tp -= std::floor (tp);
            return 1.0 - 4.0 * std::abs (tp - 0.5);
        };
        auto saw  = [] (double t) { return 2.0 * t - 1.0; };
        auto sqr  = [] (double t) { return t < 0.5 ? 1.0 : -1.0; };
        auto pulse = [] (double t, double w) { return t < w ? 1.0 : -1.0; };

        // --- klasyczne kształty (1 ramka) ---
        add (1, [=] (double t, double) { return sine (t); });
        add (1, [=] (double t, double) { return tri (t); });
        add (1, [=] (double t, double) { return saw (t); });
        add (1, [=] (double t, double) { return sqr (t); });

        // --- banki z morfingiem (8 ramek) ---

        // Morph: sine -> tri -> saw -> square -> pulse 25%
        add (nFrames, [=] (double t, double m)
        {
            const double x = m * 4.0;
            const int i = juce::jmin ((int) x, 3);
            const double f = x - (double) i;
            auto shapeAt = [&] (int k)
            {
                switch (k) { case 0: return sine (t); case 1: return tri (t); case 2: return saw (t);
                             case 3: return sqr (t);  default: return pulse (t, 0.25); }
            };
            return shapeAt (i) * (1.0 - f) + shapeAt (i + 1) * f;
        });

        // PWM: szerokość impulsu 50% -> 4%
        add (nFrames, [=] (double t, double m) { return pulse (t, 0.5 - 0.46 * m); });

        // Fold: sinus przepuszczony przez wavefolder o rosnącym wzmocnieniu
        add (nFrames, [=] (double t, double m)
        {
            const double g = 0.5 + 7.5 * m;
            return std::sin (g * std::sin (twoPi * t));
        });

        // Harmonics: piła, w której stopniowo otwiera się widmo (1 -> ~40 harmonicznych)
        add (nFrames, [=] (double t, double m)
        {
            const double hc = 1.0 + m * 40.0;
            double sum = 0.0;
            for (int k = 1; k <= 64; ++k)
            {
                const double a = juce::jlimit (0.0, 1.0, hc + 1.5 - (double) k);   // miękkie przycięcie
                if (a <= 0.0) break;
                sum -= a * std::sin (twoPi * (double) k * t) / (double) k;
            }
            return sum;
        });

        // Sync: piła z twardą synchronizacją, stosunek 1 -> 6
        add (nFrames, [=] (double t, double m)
        {
            const double r = 1.0 + 5.0 * m;
            const double x = t * r;
            return saw (x - std::floor (x));
        });

        // Vowel: widmo z dwoma formantami, A -> E -> I -> O -> U (położenie w numerach harmonicznych)
        add (nFrames, [=] (double t, double m)
        {
            static const double f1[] = { 4.0, 3.0, 2.0, 3.5, 2.0 };
            static const double f2[] = { 9.0, 12.0, 15.0, 6.0, 5.0 };
            const double x = m * 4.0;
            const int i = juce::jmin ((int) x, 3);
            const double f = x - (double) i;
            const double a = f1[i] + (f1[i + 1] - f1[i]) * f;
            const double b = f2[i] + (f2[i + 1] - f2[i]) * f;

            double sum = 0.0;
            for (int k = 1; k <= 48; ++k)
            {
                const double da = ((double) k - a) / 1.6, db = ((double) k - b) / 2.2;
                const double amp = std::exp (-da * da) + 0.7 * std::exp (-db * db) + 0.06 / (double) k;
                sum += amp * std::sin (twoPi * (double) k * t);
            }
            return sum;
        });

        // Phase Dist: sinus ze zniekształconą fazą (efekt "rezonansu" CZ)
        add (nFrames, [=] (double t, double m)
        {
            const double c = 0.5 - 0.47 * m;
            const double w = t < c ? t * 0.5 / c : 0.5 + (t - c) * 0.5 / (1.0 - c);
            return std::sin (twoPi * w);
        });

        // Digital: schodkowa piła, 64 -> 2 stopnie
        add (nFrames, [=] (double t, double m)
        {
            const double steps = 2.0 + 62.0 * (1.0 - m) * (1.0 - m);
            return std::floor ((2.0 * t - 1.0) * steps * 0.5 + 0.5) / (steps * 0.5);
        });

        // FM: sinus modulowany sinusem o 2x wyższej częstotliwości, indeks 0 -> 7
        add (nFrames, [=] (double t, double m)
        {
            return std::sin (twoPi * t + 7.0 * m * std::sin (twoPi * 2.0 * t));
        });
    }

    //--------------------------------------------------------------------------
    static void fft (std::vector<std::complex<double>>& a, bool inverse)
    {
        const size_t n = a.size();

        for (size_t i = 1, j = 0; i < n; ++i)
        {
            size_t bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j)
                std::swap (a[i], a[j]);
        }

        for (size_t len = 2; len <= n; len <<= 1)
        {
            const double ang = 6.283185307179586 / (double) len * (inverse ? 1.0 : -1.0);
            const std::complex<double> wlen (std::cos (ang), std::sin (ang));

            for (size_t i = 0; i < n; i += len)
            {
                std::complex<double> w (1.0, 0.0);
                for (size_t j = 0; j < len / 2; ++j)
                {
                    const auto u = a[i + j];
                    const auto v = a[i + j + len / 2] * w;
                    a[i + j]           = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (inverse)
            for (auto& x : a)
                x /= (double) n;
    }

    void add (int numFrames, const Shape& shape)
    {
        Table tbl;
        tbl.numFrames = numFrames;
        tbl.data.assign ((size_t) numFrames * numLevels * stride, 0.0f);

        std::vector<std::complex<double>> spec ((size_t) tableSize), work ((size_t) tableSize);

        for (int f = 0; f < numFrames; ++f)
        {
            const double morph = numFrames > 1 ? (double) f / (double) (numFrames - 1) : 0.0;

            for (int n = 0; n < tableSize; ++n)
                spec[(size_t) n] = shape ((double) n / (double) tableSize, morph);

            fft (spec, false);

            double scale = 1.0;

            for (int level = 0; level < numLevels; ++level)
            {
                const int maxH = juce::jmax (1, juce::jmin (tableSize / 2 - 1, (tableSize / 2) >> level));

                std::fill (work.begin(), work.end(), std::complex<double> (0.0, 0.0));
                for (int k = 1; k <= maxH; ++k)
                {
                    work[(size_t) k] = spec[(size_t) k];
                    work[(size_t) (tableSize - k)] = std::conj (spec[(size_t) k]);
                }

                fft (work, true);

                float* dst = tbl.data.data() + ((size_t) f * numLevels + (size_t) level) * stride;

                if (level == 0)
                {
                    double peak = 1.0e-9;
                    for (int n = 0; n < tableSize; ++n)
                        peak = std::max (peak, std::abs (work[(size_t) n].real()));
                    scale = 1.0 / peak;                 // normalizacja szczytu ramki (jedna dla wszystkich poziomów)
                }

                for (int n = 0; n < tableSize; ++n)
                    dst[n] = (float) (work[(size_t) n].real() * scale);
                dst[tableSize] = dst[0];
            }
        }

        tables.push_back (std::move (tbl));
    }

    std::vector<Table> tables;
};

//==============================================================================
/** Filtr biquad (RBJ cookbook), forma transponowana II. Bez alokacji - bezpieczny w torze audio. */
struct Biquad
{
    enum class Type { lowShelf, highShelf, peak };

    float b0 = 1.0f, b1 = 0.0f, b2 = 0.0f, a1 = 0.0f, a2 = 0.0f;
    float z1 = 0.0f, z2 = 0.0f;

    void reset() noexcept { z1 = z2 = 0.0f; }

    float process (float x) noexcept
    {
        const float y = b0 * x + z1;
        z1 = b1 * x - a1 * y + z2;
        z2 = b2 * x - a2 * y;
        return y;
    }

    void set (Type type, double sampleRate, double freq, double gainDb, double q) noexcept
    {
        freq = juce::jlimit (10.0, sampleRate * 0.49, freq);
        q    = juce::jmax (0.1, q);

        const double A     = std::pow (10.0, gainDb / 40.0);
        const double w0    = 6.283185307179586 * freq / sampleRate;
        const double cw    = std::cos (w0), sw = std::sin (w0);
        const double alpha = sw / (2.0 * q);
        const double sqA2a = 2.0 * std::sqrt (A) * alpha;

        double nb0, nb1, nb2, na0, na1, na2;

        switch (type)
        {
            case Type::peak:
                nb0 = 1.0 + alpha * A;  nb1 = -2.0 * cw;  nb2 = 1.0 - alpha * A;
                na0 = 1.0 + alpha / A;  na1 = -2.0 * cw;  na2 = 1.0 - alpha / A;
                break;

            case Type::lowShelf:
                nb0 = A * ((A + 1.0) - (A - 1.0) * cw + sqA2a);
                nb1 = 2.0 * A * ((A - 1.0) - (A + 1.0) * cw);
                nb2 = A * ((A + 1.0) - (A - 1.0) * cw - sqA2a);
                na0 = (A + 1.0) + (A - 1.0) * cw + sqA2a;
                na1 = -2.0 * ((A - 1.0) + (A + 1.0) * cw);
                na2 = (A + 1.0) + (A - 1.0) * cw - sqA2a;
                break;

            default: // highShelf
                nb0 = A * ((A + 1.0) + (A - 1.0) * cw + sqA2a);
                nb1 = -2.0 * A * ((A - 1.0) + (A + 1.0) * cw);
                nb2 = A * ((A + 1.0) + (A - 1.0) * cw - sqA2a);
                na0 = (A + 1.0) - (A - 1.0) * cw + sqA2a;
                na1 = 2.0 * ((A - 1.0) - (A + 1.0) * cw);
                na2 = (A + 1.0) - (A - 1.0) * cw - sqA2a;
                break;
        }

        b0 = (float) (nb0 / na0);  b1 = (float) (nb1 / na0);  b2 = (float) (nb2 / na0);
        a1 = (float) (na1 / na0);  a2 = (float) (na2 / na0);
    }

    /** Moduł odpowiedzi w dB dla częstotliwości f (do rysowania krzywej w edytorze). */
    double magnitudeDb (double f, double sampleRate) const noexcept
    {
        const double w = 6.283185307179586 * f / sampleRate;
        const std::complex<double> z1c (std::cos (-w), std::sin (-w));
        const std::complex<double> z2c = z1c * z1c;
        const auto num = (double) b0 + (double) b1 * z1c + (double) b2 * z2c;
        const auto den = 1.0 + (double) a1 * z1c + (double) a2 * z2c;
        return 20.0 * std::log10 (std::max (1.0e-9, std::abs (num / den)));
    }
};

//==============================================================================
/** Kompresor feed-forward z miękkim kolanem, makeup i parallel mix. Mono. */
class Compressor
{
public:
    static constexpr float kneeDb = 6.0f;

    void prepare (double sr)
    {
        sampleRate = sr;
        detCoeff = (float) std::exp (-1.0 / (0.025 * sr));      // detektor: ~25 ms, wygładza przebieg basu
        reset();
    }

    void reset() noexcept { det = 0.0f; grState = 0.0f; grMin = 0.0f; }

    void setParams (float threshDb, float ratio, float attackMs, float releaseMs, float makeupDb, float mixAmount)
    {
        thresh = threshDb;
        ratioV = juce::jmax (1.0f, ratio);
        attCoeff = (float) std::exp (-1.0 / (juce::jmax (0.05f, attackMs)  * 0.001 * sampleRate));
        relCoeff = (float) std::exp (-1.0 / (juce::jmax (1.0f,  releaseMs) * 0.001 * sampleRate));
        makeup = makeupDb;
        mix = juce::jlimit (0.0f, 1.0f, mixAmount);
    }

    /** Poziom wyjściowy (dB) dla poziomu wejściowego (dB) - krzywa transferowa z kolanem. */
    static float transferDb (float inDb, float threshDb, float ratio, float knee = kneeDb) noexcept
    {
        const float over = inDb - threshDb;
        if (2.0f * over < -knee)
            return inDb;
        if (2.0f * std::abs (over) <= knee)
        {
            const float t = over + knee * 0.5f;
            return inDb + (1.0f / ratio - 1.0f) * t * t / (2.0f * knee);
        }
        return threshDb + over / ratio;
    }

    float process (float x) noexcept
    {
        const float a = std::abs (x);
        det = a > det ? a : det * detCoeff;           // szczyt z wolnym opadaniem

        const float inDb  = 20.0f * std::log10 (juce::jmax (det, 1.0e-6f));
        const float grDb  = transferDb (inDb, thresh, ratioV) - inDb;      // <= 0

        const float coeff = grDb < grState ? attCoeff : relCoeff;
        grState = grDb + coeff * (grState - grDb);
        grMin = juce::jmin (grMin, grState);

        const float g = std::exp ((grState + makeup) * 0.11512925f);       // dB -> liniowo
        return x * (1.0f - mix) + x * g * mix;
    }

    /** Największa redukcja (dB, <= 0) od ostatniego wywołania; zeruje licznik. */
    float takeGainReduction() noexcept
    {
        const float v = grMin;
        grMin = grState;
        return v;
    }

private:
    double sampleRate = 44100.0;
    float thresh = -18.0f, ratioV = 4.0f, makeup = 0.0f, mix = 1.0f;
    float attCoeff = 0.99f, relCoeff = 0.999f, detCoeff = 0.99f;
    float det = 0.0f, grState = 0.0f, grMin = 0.0f;
};
