#pragma once

#include "PluginProcessor.h"
#include "Parameters.h"
#include "Theme.h"
#include "Dsp.h"

//==============================================================================
/** Oscyloskop na żywo (z wyzwalaniem na narastającym przejściu przez zero). */
class ScopeDisplay : public juce::Component, private juce::Timer
{
public:
    explicit ScopeDisplay (BassoraAudioProcessor& p) : proc (p) { startTimerHz (30); }

    void paint (juce::Graphics& g) override
    {
        const auto full = getLocalBounds().toFloat();
        Theme::drawScreen (g, full);

        const auto r = full.reduced (12.0f, 16.0f);

        // siatka
        g.setColour (Theme::ice.withAlpha (0.07f));
        g.drawHorizontalLine ((int) r.getCentreY(), r.getX(), r.getRight());
        for (int i = 1; i < 6; ++i)
            g.drawVerticalLine ((int) (r.getX() + r.getWidth() * (float) i / 6.0f), r.getY(), r.getBottom());

        float data[4096];
        proc.getScopeData (data, 4096);

        int start = 0;
        for (int i = 1; i < 2048; ++i)
            if (data[i - 1] <= 0.0f && data[i] > 0.0f) { start = i; break; }

        constexpr int count = 1800;
        juce::Path wave;
        for (int i = 0; i < count; ++i)
        {
            const float x = r.getX() + r.getWidth() * (float) i / (float) (count - 1);
            const float y = r.getCentreY() - data[start + i] * r.getHeight() * 0.46f;
            if (i == 0) wave.startNewSubPath (x, y); else wave.lineTo (x, y);
        }

        juce::Path fill (wave);
        fill.lineTo (r.getRight(), r.getCentreY());
        fill.lineTo (r.getX(), r.getCentreY());
        fill.closeSubPath();
        g.setGradientFill (juce::ColourGradient (Theme::ice.withAlpha (0.20f), 0.0f, r.getY(),
                                                 Theme::steel.withAlpha (0.05f), 0.0f, r.getBottom(), false));
        g.fillPath (fill);

        Theme::softLine (g, wave, Theme::ice, 1.6f);

        g.setColour (Theme::textDim);
        g.setFont (Theme::font (11.0f, true));
        g.drawText ("Output", full.reduced (14.0f, 7.0f).removeFromTop (13.0f), juce::Justification::centredLeft);
    }

private:
    void timerCallback() override { repaint(); }

    BassoraAudioProcessor& proc;
};

//==============================================================================
/** Edytor obwiedni ADSR: przeciągaj uchwyty (A, D/S, R) myszką. */
class EnvelopeEditor : public juce::Component, private juce::Timer
{
public:
    explicit EnvelopeEditor (juce::AudioProcessorValueTreeState& apvts)
        : pA (apvts.getParameter (IDs::attack)),
          pD (apvts.getParameter (IDs::decay)),
          pS (apvts.getParameter (IDs::sustain)),
          pR (apvts.getParameter (IDs::release))
    {
        startTimerHz (30);
    }

    void paint (juce::Graphics& g) override
    {
        Theme::drawScreen (g, getLocalBounds().toFloat());
        const auto geo = getGeo();

        g.setColour (Theme::ice.withAlpha (0.07f));
        for (int i = 0; i <= 4; ++i)
        {
            g.drawVerticalLine ((int) (geo.r.getX() + geo.r.getWidth() * (float) i / 4.0f), geo.r.getY(), geo.r.getBottom());
            g.drawHorizontalLine ((int) (geo.r.getY() + geo.r.getHeight() * (float) i / 4.0f), geo.r.getX(), geo.r.getRight());
        }

        juce::Path curve;
        curve.startNewSubPath (geo.p0);
        curve.lineTo (geo.p1);
        curve.lineTo (geo.p2);
        curve.lineTo (geo.p3);
        curve.lineTo (geo.p4);

        juce::Path fill (curve);
        fill.closeSubPath();
        g.setGradientFill (juce::ColourGradient (Theme::steel.withAlpha (0.42f), 0.0f, geo.r.getY(),
                                                 Theme::steel.withAlpha (0.0f),  0.0f, geo.r.getBottom(), false));
        g.fillPath (fill);

        Theme::softLine (g, curve, Theme::ice, 2.0f);

        const juce::Point<float> pts[] = { geo.p1, geo.p2, geo.p4 };
        const char* names[] = { "A", "D / S", "R" };
        for (int i = 0; i < 3; ++i)
        {
            const bool hot = (hover == i || drag == i);
            Theme::handle (g, pts[i], hot ? 6.5f : 5.2f, hot ? Theme::ice : Theme::steel, hot);

            g.setColour (Theme::textDim);
            g.setFont (Theme::font (10.5f, true));
            g.drawText (names[i], juce::Rectangle<float> (pts[i].x - 20.0f, pts[i].y - 24.0f, 40.0f, 12.0f),
                        juce::Justification::centred);
        }

        g.setColour (Theme::text.withAlpha (0.85f));
        g.setFont (Theme::font (11.5f, true));
        const auto txt = "Atk " + show (pA) + "    Dec " + show (pD) + "    Sus " + show (pS) + "    Rel " + show (pR);
        g.drawText (txt, getLocalBounds().toFloat().reduced (14.0f, 9.0f).removeFromTop (15.0f),
                    juce::Justification::centredLeft);
    }

    void mouseDown (const juce::MouseEvent& e) override
    {
        drag = hitTest (getGeo(), e.position);
        if (drag >= 0)
        {
            for (auto* p : { pA, pD, pS, pR })
                p->beginChangeGesture();
            mouseDrag (e);
        }
    }

    void mouseDrag (const juce::MouseEvent& e) override
    {
        if (drag < 0)
            return;

        const auto geo = getGeo();
        const float top = geo.r.getY(), bottom = geo.r.getBottom();

        if (drag == 0)
        {
            setNorm (pA, (e.position.x - geo.p0.x) / geo.segA);
        }
        else if (drag == 1)
        {
            setNorm (pD, (e.position.x - geo.p1.x) / geo.segD);
            setNorm (pS, (bottom - e.position.y) / (bottom - top));
        }
        else
        {
            setNorm (pR, (e.position.x - geo.p3.x) / geo.segR);
        }
        repaint();
    }

    void mouseUp (const juce::MouseEvent&) override
    {
        if (drag >= 0)
            for (auto* p : { pA, pD, pS, pR })
                p->endChangeGesture();
        drag = -1;
    }

    void mouseMove (const juce::MouseEvent& e) override
    {
        const int h = hitTest (getGeo(), e.position);
        if (h != hover) { hover = h; repaint(); }
    }

    void mouseExit (const juce::MouseEvent&) override { hover = -1; repaint(); }

private:
    struct Geo
    {
        juce::Rectangle<float> r;
        float segA = 0, segD = 0, hold = 0, segR = 0;
        juce::Point<float> p0, p1, p2, p3, p4;
    };

    Geo getGeo() const
    {
        Geo geo;
        geo.r = getLocalBounds().toFloat().reduced (22.0f, 0.0f).withTrimmedTop (42.0f).withTrimmedBottom (20.0f);

        const float W = geo.r.getWidth();
        geo.segA = W * 0.22f;
        geo.segD = W * 0.30f;
        geo.hold = W * 0.14f;
        geo.segR = W * 0.34f;

        const float top = geo.r.getY(), bottom = geo.r.getBottom();
        geo.p0 = { geo.r.getX(), bottom };
        geo.p1 = { geo.p0.x + pA->getValue() * geo.segA, top };
        geo.p2 = { geo.p1.x + pD->getValue() * geo.segD, bottom - pS->getValue() * (bottom - top) };
        geo.p3 = { geo.p2.x + geo.hold, geo.p2.y };
        geo.p4 = { geo.p3.x + pR->getValue() * geo.segR, bottom };
        return geo;
    }

    int hitTest (const Geo& geo, juce::Point<float> pos) const
    {
        const juce::Point<float> pts[] = { geo.p1, geo.p2, geo.p4 };
        int best = -1;
        float bestD = 18.0f;
        for (int i = 0; i < 3; ++i)
        {
            const float d = pts[i].getDistanceFrom (pos);
            if (d < bestD) { bestD = d; best = i; }
        }
        return best;
    }

    static void setNorm (juce::RangedAudioParameter* p, float v)
    {
        p->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, v));
    }

    static juce::String show (juce::RangedAudioParameter* p)
    {
        return p->getCurrentValueAsText() + p->getLabel();
    }

    void timerCallback() override { repaint(); }

    juce::RangedAudioParameter *pA, *pD, *pS, *pR;
    int drag = -1, hover = -1;
};

//==============================================================================
/** Wykres odpowiedzi filtra low-pass. Przeciągaj uchwyt: X = cutoff, Y = rezonans. */
class FilterPad : public juce::Component, private juce::Timer
{
public:
    explicit FilterPad (juce::AudioProcessorValueTreeState& apvts)
        : pCut (apvts.getParameter (IDs::cutoff)),
          pRes (apvts.getParameter (IDs::reso))
    {
        startTimerHz (30);
    }

    void paint (juce::Graphics& g) override
    {
        Theme::drawScreen (g, getLocalBounds().toFloat());
        const auto r = area();

        g.setFont (Theme::font (10.5f, true));
        for (float f : { 100.0f, 1000.0f, 10000.0f })
        {
            const float x = xFor (f, r);
            g.setColour (Theme::ice.withAlpha (0.07f));
            g.drawVerticalLine ((int) x, r.getY(), r.getBottom());
            g.setColour (Theme::textDim);
            g.drawText (f >= 1000.0f ? juce::String ((int) (f / 1000.0f)) + "k" : juce::String ((int) f),
                        (int) x - 16, (int) r.getBottom() - 12, 32, 12, juce::Justification::centred);
        }
        g.setColour (Theme::ice.withAlpha (0.10f));
        g.drawHorizontalLine ((int) yFor (0.0f, r), r.getX(), r.getRight());

        juce::Path curve;
        for (float px = 0.0f; px <= r.getWidth(); px += 2.0f)
        {
            const float f = fMin * std::pow (fMax / fMin, px / r.getWidth());
            const float y = yFor (magDb (f), r);
            if (px == 0.0f) curve.startNewSubPath (r.getX() + px, y);
            else            curve.lineTo (r.getX() + px, y);
        }

        juce::Path fill (curve);
        fill.lineTo (r.getRight(), r.getBottom());
        fill.lineTo (r.getX(), r.getBottom());
        fill.closeSubPath();
        g.setGradientFill (juce::ColourGradient (Theme::aqua.withAlpha (0.32f), 0.0f, r.getY(),
                                                 Theme::aqua.withAlpha (0.02f), 0.0f, r.getBottom(), false));
        g.fillPath (fill);

        Theme::softLine (g, curve, Theme::aqua, 2.0f);

        const juce::Point<float> h { xFor (cutoffHz(), r), yFor (20.0f * std::log10 (q()), r) };
        g.setColour (Theme::aqua.withAlpha (0.25f));
        g.drawLine (h.x, r.getY(), h.x, r.getBottom(), 1.0f);
        Theme::handle (g, h, dragging ? 6.5f : 5.4f, Theme::ice, dragging);

        g.setColour (Theme::textDim);
        g.setFont (Theme::font (11.0f, true));
        g.drawText ("Cutoff " + pCut->getCurrentValueAsText() + " Hz     Reso " + pRes->getCurrentValueAsText(),
                    getLocalBounds().toFloat().reduced (14.0f, 7.0f).removeFromTop (13.0f),
                    juce::Justification::centredLeft);
    }

    void mouseDown (const juce::MouseEvent& e) override
    {
        dragging = true;
        pCut->beginChangeGesture();
        pRes->beginChangeGesture();
        mouseDrag (e);
    }

    void mouseDrag (const juce::MouseEvent& e) override
    {
        const auto r = area();

        const float nx = juce::jlimit (0.0f, 1.0f, (e.position.x - r.getX()) / r.getWidth());
        const float f  = fMin * std::pow (fMax / fMin, nx);
        pCut->setValueNotifyingHost (pCut->convertTo0to1 (f));

        const float db = dbMin + (r.getBottom() - e.position.y) / r.getHeight() * (dbMax - dbMin);
        const float Q  = std::pow (10.0f, db / 20.0f);
        pRes->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, (Q - 0.707f) / 6.0f));
        repaint();
    }

    void mouseUp (const juce::MouseEvent&) override
    {
        dragging = false;
        pCut->endChangeGesture();
        pRes->endChangeGesture();
        repaint();
    }

private:
    static constexpr float fMin = 20.0f, fMax = 20000.0f, dbMin = -30.0f, dbMax = 24.0f;

    juce::Rectangle<float> area() const { return getLocalBounds().toFloat().reduced (14.0f, 22.0f); }

    float cutoffHz() const { return pCut->convertFrom0to1 (pCut->getValue()); }
    float q() const        { return 0.707f + pRes->convertFrom0to1 (pRes->getValue()) * 6.0f; }

    static float xFor (float f, juce::Rectangle<float> r)
    {
        return r.getX() + r.getWidth() * std::log (f / fMin) / std::log (fMax / fMin);
    }

    static float yFor (float db, juce::Rectangle<float> r)
    {
        const float n = juce::jlimit (0.0f, 1.0f, (db - dbMin) / (dbMax - dbMin));
        return r.getBottom() - n * r.getHeight();
    }

    float magDb (float f) const
    {
        const float u = f / cutoffHz();
        const float Q = q();
        const float a = 1.0f - u * u;
        const float mag = 1.0f / std::sqrt (a * a + (u / Q) * (u / Q));
        return 20.0f * std::log10 (mag);
    }

    void timerCallback() override { repaint(); }

    juce::RangedAudioParameter *pCut, *pRes;
    bool dragging = false;
};

//==============================================================================
/** Wykres EQ: trzy uchwyty (low shelf, mid peak, high shelf). X = częstotliwość, Y = wzmocnienie.
    Kółko myszy nad uchwytem MID zmienia jego dobroć (Q). Podwójne kliknięcie zeruje wzmocnienie pasma. */
class EqPad : public juce::Component, private juce::Timer
{
public:
    explicit EqPad (BassoraAudioProcessor& p)
    {
        auto& a = p.apvts;
        pOn = a.getParameter (IDs::eqOn);
        pMidQ = a.getParameter (IDs::eqMidQ);

        nodes[0] = { a.getParameter (IDs::eqLoF),  a.getParameter (IDs::eqLoG),  Theme::steel, "Low" };
        nodes[1] = { a.getParameter (IDs::eqMidF), a.getParameter (IDs::eqMidG), Theme::ice,  "Mid" };
        nodes[2] = { a.getParameter (IDs::eqHiF),  a.getParameter (IDs::eqHiG),  Theme::aqua,   "High" };

        startTimerHz (30);
    }

    void paint (juce::Graphics& g) override
    {
        const bool on = pOn->getValue() > 0.5f;
        Theme::drawScreen (g, getLocalBounds().toFloat());
        const auto r = area();

        g.setFont (Theme::font (10.5f, true));
        for (float f : { 50.0f, 100.0f, 500.0f, 1000.0f, 5000.0f, 10000.0f })
        {
            const float x = xFor (f, r);
            g.setColour (Theme::ice.withAlpha (0.06f));
            g.drawVerticalLine ((int) x, r.getY(), r.getBottom());
            g.setColour (Theme::textDim.withAlpha (0.9f));
            const auto label = f >= 1000.0f ? juce::String ((int) (f / 1000.0f)) + "k" : juce::String ((int) f);
            g.drawText (label, (int) x - 16, (int) r.getBottom() + 1, 32, 12, juce::Justification::centred);
        }

        for (float db : { -12.0f, -6.0f, 0.0f, 6.0f, 12.0f })
        {
            const float y = yFor (db, r);
            g.setColour (Theme::ice.withAlpha (db == 0.0f ? 0.16f : 0.06f));
            g.drawHorizontalLine ((int) y, r.getX(), r.getRight());
            if (db != 0.0f)
            {
                g.setColour (Theme::textDim.withAlpha (0.7f));
                g.drawText ((db > 0 ? "+" : "") + juce::String ((int) db), (int) r.getX() - 4, (int) y - 6, 24, 12,
                            juce::Justification::centredLeft);
            }
        }

        // krzywa wypadkowa
        Biquad lo, mid, hi;
        configure (lo, mid, hi);

        juce::Path curve;
        const float y0 = yFor (0.0f, r);
        for (float px = 0.0f; px <= r.getWidth(); px += 2.0f)
        {
            const double f = (double) fMin * std::pow ((double) fMax / (double) fMin, (double) px / (double) r.getWidth());
            const float db = (float) (lo.magnitudeDb (f, sr()) + mid.magnitudeDb (f, sr()) + hi.magnitudeDb (f, sr()));
            const float y = yFor (db, r);
            if (px == 0.0f) curve.startNewSubPath (r.getX(), y);
            else            curve.lineTo (r.getX() + px, y);
        }

        juce::Path fill (curve);
        fill.lineTo (r.getRight(), y0);
        fill.lineTo (r.getX(), y0);
        fill.closeSubPath();

        const auto accent = on ? Theme::ice : Theme::textDim;
        g.setGradientFill (juce::ColourGradient (accent.withAlpha (0.26f), 0.0f, r.getY(),
                                                 accent.withAlpha (0.04f), 0.0f, r.getBottom(), false));
        g.fillPath (fill);
        Theme::softLine (g, curve, accent, 2.0f);

        // uchwyty
        for (int i = 0; i < 3; ++i)
        {
            const auto c = nodePos (i, r);
            const bool hot = (hover == i || drag == i);
            Theme::handle (g, c, hot ? 7.0f : 5.6f, on ? nodes[(size_t) i].colour : Theme::textDim, hot);

            g.setColour (Theme::textDim);
            g.setFont (Theme::font (10.5f, true));
            g.drawText (nodes[(size_t) i].name, juce::Rectangle<float> (c.x - 20.0f, c.y - 25.0f, 40.0f, 12.0f),
                        juce::Justification::centred);
        }

        // odczyt aktywnego pasma
        const int shown = drag >= 0 ? drag : hover;
        g.setColour (Theme::text.withAlpha (0.85f));
        g.setFont (Theme::font (11.5f, true));
        juce::String info = "Drag the dots  -  wheel on Mid changes Q";
        if (shown >= 0)
        {
            const auto& n = nodes[(size_t) shown];
            info = juce::String (n.name) + "  " + n.freq->getCurrentValueAsText() + " Hz   " + n.gain->getCurrentValueAsText() + " dB";
            if (shown == 1)
                info += "   Q " + pMidQ->getCurrentValueAsText();
        }
        g.drawText (info, getLocalBounds().toFloat().reduced (14.0f, 7.0f).removeFromTop (13.0f),
                    juce::Justification::centredLeft);
    }

    void mouseDown (const juce::MouseEvent& e) override
    {
        drag = hitTest (e.position);
        if (drag >= 0)
        {
            nodes[(size_t) drag].freq->beginChangeGesture();
            nodes[(size_t) drag].gain->beginChangeGesture();
            mouseDrag (e);
        }
    }

    void mouseDrag (const juce::MouseEvent& e) override
    {
        if (drag < 0)
            return;

        const auto r = area();
        auto& n = nodes[(size_t) drag];

        const float nx = juce::jlimit (0.0f, 1.0f, (e.position.x - r.getX()) / r.getWidth());
        n.freq->setValueNotifyingHost (n.freq->convertTo0to1 (fMin * std::pow (fMax / fMin, nx)));

        const float db = dbMin + (r.getBottom() - e.position.y) / r.getHeight() * (dbMax - dbMin);
        n.gain->setValueNotifyingHost (n.gain->convertTo0to1 (db));
        repaint();
    }

    void mouseUp (const juce::MouseEvent&) override
    {
        if (drag >= 0)
        {
            nodes[(size_t) drag].freq->endChangeGesture();
            nodes[(size_t) drag].gain->endChangeGesture();
        }
        drag = -1;
        repaint();
    }

    void mouseDoubleClick (const juce::MouseEvent& e) override
    {
        const int i = hitTest (e.position);
        if (i >= 0)
        {
            auto* g = nodes[(size_t) i].gain;
            g->beginChangeGesture();
            g->setValueNotifyingHost (g->getDefaultValue());
            g->endChangeGesture();
        }
    }

    void mouseMove (const juce::MouseEvent& e) override
    {
        const int h = hitTest (e.position);
        if (h != hover) { hover = h; repaint(); }
    }

    void mouseExit (const juce::MouseEvent&) override { hover = -1; repaint(); }

    void mouseWheelMove (const juce::MouseEvent& e, const juce::MouseWheelDetails& w) override
    {
        if (hitTest (e.position) == 1)
        {
            pMidQ->beginChangeGesture();
            pMidQ->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, pMidQ->getValue() + w.deltaY * 0.5f));
            pMidQ->endChangeGesture();
            repaint();
        }
    }

private:
    struct Node
    {
        juce::RangedAudioParameter* freq = nullptr;
        juce::RangedAudioParameter* gain = nullptr;
        juce::Colour colour;
        const char* name = "";
    };

    static constexpr float fMin = 20.0f, fMax = 20000.0f, dbMin = -15.0f, dbMax = 15.0f;

    juce::Rectangle<float> area() const { return getLocalBounds().toFloat().reduced (22.0f, 24.0f).withTrimmedBottom (4.0f); }
    double sr() const { return 48000.0; }       // do rysowania wystarczy stała

    float value (juce::RangedAudioParameter* p) const { return p->convertFrom0to1 (p->getValue()); }

    void configure (Biquad& lo, Biquad& mid, Biquad& hi) const
    {
        lo.set  (Biquad::Type::lowShelf,  sr(), value (nodes[0].freq), value (nodes[0].gain), 0.707);
        mid.set (Biquad::Type::peak,      sr(), value (nodes[1].freq), value (nodes[1].gain), value (pMidQ));
        hi.set  (Biquad::Type::highShelf, sr(), value (nodes[2].freq), value (nodes[2].gain), 0.707);
    }

    juce::Point<float> nodePos (int i, juce::Rectangle<float> r) const
    {
        return { xFor (value (nodes[(size_t) i].freq), r), yFor (value (nodes[(size_t) i].gain), r) };
    }

    int hitTest (juce::Point<float> pos) const
    {
        const auto r = area();
        int best = -1;
        float bestD = 20.0f;
        for (int i = 0; i < 3; ++i)
        {
            const float d = nodePos (i, r).getDistanceFrom (pos);
            if (d < bestD) { bestD = d; best = i; }
        }
        return best;
    }

    static float xFor (float f, juce::Rectangle<float> r)
    {
        return r.getX() + r.getWidth() * std::log (f / fMin) / std::log (fMax / fMin);
    }

    static float yFor (float db, juce::Rectangle<float> r)
    {
        const float n = juce::jlimit (0.0f, 1.0f, (db - dbMin) / (dbMax - dbMin));
        return r.getBottom() - n * r.getHeight();
    }

    void timerCallback() override { repaint(); }

    juce::RangedAudioParameter *pOn = nullptr, *pMidQ = nullptr;
    std::array<Node, 3> nodes;
    int drag = -1, hover = -1;
};

//==============================================================================
/** Krzywa transferowa kompresora + miernik redukcji wzmocnienia na żywo. */
class CompDisplay : public juce::Component, private juce::Timer
{
public:
    explicit CompDisplay (BassoraAudioProcessor& p) : proc (p)
    {
        auto& a = p.apvts;
        pOn     = a.getParameter (IDs::compOn);
        pThresh = a.getParameter (IDs::compThresh);
        pRatio  = a.getParameter (IDs::compRatio);
        pMakeup = a.getParameter (IDs::compMakeup);
        pMix    = a.getParameter (IDs::compMix);
        startTimerHz (30);
    }

    void paint (juce::Graphics& g) override
    {
        const bool on = pOn->getValue() > 0.5f;
        Theme::drawScreen (g, getLocalBounds().toFloat());

        auto full = getLocalBounds().toFloat().reduced (12.0f, 22.0f);
        auto meter = full.removeFromRight (16.0f);
        full.removeFromRight (14.0f);
        const auto r = full.withTrimmedBottom (4.0f);

        // siatka
        for (float db : { -48.0f, -36.0f, -24.0f, -12.0f, 0.0f })
        {
            g.setColour (Theme::ice.withAlpha (0.06f));
            g.drawVerticalLine ((int) xFor (db, r), r.getY(), r.getBottom());
            g.drawHorizontalLine ((int) yFor (db, r), r.getX(), r.getRight());
        }

        // przekątna 1:1
        juce::Path unity;
        unity.startNewSubPath (xFor (dbMin, r), yFor (dbMin, r));
        unity.lineTo (xFor (0.0f, r), yFor (0.0f, r));
        g.setColour (Theme::textDim.withAlpha (0.35f));
        g.strokePath (unity, juce::PathStrokeType (1.0f));

        const float T = value (pThresh), R = value (pRatio), mk = value (pMakeup), mix = value (pMix);

        juce::Path curve;
        for (float in = dbMin; in <= 0.001f; in += 1.0f)
        {
            const float outWet = Compressor::transferDb (in, T, R) + mk;
            const float lin = std::pow (10.0f, in / 20.0f) * (1.0f - mix) + std::pow (10.0f, outWet / 20.0f) * mix;
            const float out = 20.0f * std::log10 (juce::jmax (lin, 1.0e-6f));
            const float x = xFor (in, r), y = yFor (out, r);
            if (in == dbMin) curve.startNewSubPath (x, y); else curve.lineTo (x, y);
        }

        const auto accent = on ? Theme::steel : Theme::textDim;
        Theme::softLine (g, curve, accent, 2.0f);

        // próg
        const float tx = xFor (T, r);
        g.setColour (Theme::ice.withAlpha (on ? 0.55f : 0.2f));
        const float dashes[] = { 3.0f, 3.0f };
        g.drawDashedLine (juce::Line<float> (tx, r.getY(), tx, r.getBottom()), dashes, 2, 1.0f);
        Theme::handle (g, { tx, yFor (T, r) }, 4.2f, on ? Theme::ice : Theme::textDim);

        // miernik GR (0 .. -24 dB, od góry w dół)
        meterDb += ((on ? proc.getCompGainReduction() : 0.0f) - meterDb) * 0.4f;
        g.setColour (juce::Colour (0xff17120e));
        g.fillRoundedRectangle (meter, 4.0f);
        const float frac = juce::jlimit (0.0f, 1.0f, -meterDb / 24.0f);
        if (frac > 0.0f)
        {
            auto bar = meter.withHeight (meter.getHeight() * frac);
            g.setGradientFill (juce::ColourGradient (Theme::ice, 0.0f, meter.getY(),
                                                     Theme::steel, 0.0f, meter.getBottom(), false));
            g.fillRoundedRectangle (bar, 4.0f);
        }
        g.setColour (Theme::stroke);
        g.drawRoundedRectangle (meter, 4.0f, 1.0f);

        g.setColour (Theme::textDim);
        g.setFont (Theme::font (11.0f, true));
        g.drawText ("Gain reduction  " + juce::String (-meterDb, 1) + " dB",
                    getLocalBounds().toFloat().reduced (14.0f, 7.0f).removeFromTop (13.0f),
                    juce::Justification::centredLeft);
    }

private:
    static constexpr float dbMin = -60.0f, dbMax = 12.0f;

    static float xFor (float db, juce::Rectangle<float> r)
    {
        return r.getX() + r.getWidth() * (db - dbMin) / (0.0f - dbMin);
    }

    static float yFor (float db, juce::Rectangle<float> r)
    {
        const float n = juce::jlimit (0.0f, 1.0f, (db - dbMin) / (dbMax - dbMin));
        return r.getBottom() - n * r.getHeight();
    }

    float value (juce::RangedAudioParameter* p) const { return p->convertFrom0to1 (p->getValue()); }

    void timerCallback() override { repaint(); }

    BassoraAudioProcessor& proc;
    juce::RangedAudioParameter *pOn, *pThresh, *pRatio, *pMakeup, *pMix;
    float meterDb = 0.0f;
};
