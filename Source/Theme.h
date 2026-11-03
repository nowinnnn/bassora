#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

//==============================================================================
// Styl z logo BASSORA: głęboka czerń, płyty z ciemnego "kamienia", chłodna stal i lodowy błękit.
// Jedyny mocny akcent to cienka, jasna "szczelina światła" - jak linia przecinająca emblemat.
//==============================================================================
namespace Theme
{
    inline const juce::Colour bg        { 0xff040508 };
    inline const juce::Colour panelTop  { 0xff1a1e25 };
    inline const juce::Colour panelBot  { 0xff0b0d11 };
    inline const juce::Colour stroke    { 0xff2a303a };
    inline const juce::Colour text      { 0xffe9eef6 };
    inline const juce::Colour textDim   { 0xff7f8a9b };
    inline const juce::Colour ice       { 0xffb4dcff };     // główny akcent
    inline const juce::Colour steel     { 0xff6aa6e6 };
    inline const juce::Colour aqua      { 0xff8fd8ee };
    inline const juce::Colour silver    { 0xffcdd4de };

    inline juce::Font font (float height, bool bold = false)
    {
        return juce::Font (juce::FontOptions (height, bold ? juce::Font::bold : juce::Font::plain));
    }

    /** Rozstrzelony, pisany wersalikami krój (jak podtytuł w logo). */
    inline juce::Font tracked (float height, bool bold = true, float kerning = 0.16f)
    {
        return font (height, bold).withExtraKerningFactor (kerning);
    }

    /** Linia z delikatną poświatą (używana na ekranach/wykresach). */
    inline void softLine (juce::Graphics& g, const juce::Path& p, juce::Colour c, float width)
    {
        g.setColour (c.withAlpha (0.09f));
        g.strokePath (p, juce::PathStrokeType (width + 6.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        g.setColour (c.withAlpha (0.17f));
        g.strokePath (p, juce::PathStrokeType (width + 3.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        g.setColour (c);
        g.strokePath (p, juce::PathStrokeType (width, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    /** Uchwyt na wykresie: jasny "otoczak" z miękkim cieniem. */
    inline void handle (juce::Graphics& g, juce::Point<float> c, float r, juce::Colour col, bool hot = false)
    {
        g.setColour (juce::Colours::black.withAlpha (0.55f));
        g.fillEllipse (c.x - r - 1.0f, c.y - r + 1.5f, (r + 1.0f) * 2.0f, (r + 1.0f) * 2.0f);

        if (hot)
        {
            g.setGradientFill (juce::ColourGradient (col.withAlpha (0.38f), c.x, c.y,
                                                     col.withAlpha (0.0f),  c.x + r + 9.0f, c.y, true));
            g.fillEllipse (c.x - r - 9.0f, c.y - r - 9.0f, (r + 9.0f) * 2.0f, (r + 9.0f) * 2.0f);
        }

        g.setGradientFill (juce::ColourGradient (juce::Colours::white, c.x - r * 0.4f, c.y - r * 0.6f,
                                                 col.darker (0.3f), c.x + r * 0.5f, c.y + r, false));
        g.fillEllipse (c.x - r, c.y - r, r * 2.0f, r * 2.0f);

        g.setColour (juce::Colours::white.withAlpha (0.6f));
        g.drawEllipse (c.x - r, c.y - r, r * 2.0f, r * 2.0f, 1.0f);
    }

    /** Wgłębiony "ekran" - czarne szkło z cienką chłodną krawędzią. */
    inline void drawScreen (juce::Graphics& g, juce::Rectangle<float> r)
    {
        g.setGradientFill (juce::ColourGradient (juce::Colour (0xff07090c), r.getX(), r.getY(),
                                                 juce::Colour (0xff020304), r.getX(), r.getBottom(), false));
        g.fillRoundedRectangle (r, 10.0f);

        g.setColour (juce::Colours::black.withAlpha (0.9f));
        g.drawRoundedRectangle (r.reduced (0.75f), 10.0f, 1.5f);
        g.setColour (ice.withAlpha (0.09f));
        g.drawRoundedRectangle (r.reduced (1.75f), 9.0f, 1.0f);
    }

    /** Płyta z ciemnego kamienia: gradient, miękki cień, chłodny odblask u góry, "szczelina światła" przy tytule. */
    inline void drawPanel (juce::Graphics& g, juce::Rectangle<float> r,
                           const juce::String& title, juce::Colour accent)
    {
        juce::Path p;
        p.addRoundedRectangle (r, 16.0f);

        juce::DropShadow (juce::Colours::black.withAlpha (0.85f), 26, { 0, 10 }).drawForPath (g, p);

        g.setGradientFill (juce::ColourGradient (panelTop, r.getX(), r.getY(), panelBot, r.getX(), r.getBottom(), false));
        g.fillPath (p);

        // miękkie światło z góry (kamień oświetlony z jednej strony)
        g.saveState();
        g.reduceClipRegion (p);
        g.setGradientFill (juce::ColourGradient (accent.withAlpha (0.10f), r.getCentreX(), r.getY() - 10.0f,
                                                 accent.withAlpha (0.0f),  r.getCentreX(), r.getY() + r.getHeight() * 0.55f, true));
        g.fillRect (r);
        g.restoreState();

        g.setColour (stroke);
        g.drawRoundedRectangle (r.reduced (0.5f), 16.0f, 1.0f);

        // jasna krawędź u góry
        g.saveState();
        g.reduceClipRegion (r.getSmallestIntegerContainer().withHeight (4));
        g.setColour (juce::Colour (0xffd8ecff).withAlpha (0.16f));
        g.drawRoundedRectangle (r.reduced (1.5f), 15.0f, 1.0f);
        g.restoreState();

        // szczelina światła + tytuł
        const float lx = r.getX() + 19.0f, ly = r.getY() + 14.0f;
        g.setColour (accent.withAlpha (0.18f));
        g.fillRoundedRectangle (lx - 2.5f, ly - 2.0f, 6.0f, 22.0f, 3.0f);
        g.setGradientFill (juce::ColourGradient (juce::Colours::white, lx, ly, accent, lx, ly + 18.0f, false));
        g.fillRoundedRectangle (lx, ly, 1.6f, 18.0f, 0.8f);

        g.setColour (silver.withAlpha (0.95f));
        g.setFont (tracked (11.5f));
        g.drawText (title.toUpperCase(), juce::Rectangle<float> (r.getX() + 32.0f, r.getY() + 12.0f, r.getWidth() - 70.0f, 22.0f),
                    juce::Justification::centredLeft);
    }
}

//==============================================================================
// LookAndFeel: gałki-otoczaki z odblaskiem krawędziowym i cienkim wskaźnikiem-"szczeliną"
//==============================================================================
class AnalogLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AnalogLookAndFeel()
    {
        using namespace juce;
        setColour (ResizableWindow::backgroundColourId,       Theme::bg);
        setColour (PopupMenu::backgroundColourId,             Colour (0xff0d1014));
        setColour (PopupMenu::textColourId,                   Theme::text);
        setColour (PopupMenu::headerTextColourId,             Theme::ice);
        setColour (PopupMenu::highlightedBackgroundColourId,  Theme::steel.withAlpha (0.45f));
        setColour (PopupMenu::highlightedTextColourId,        Colours::white);
        setColour (ComboBox::textColourId,                    Theme::text);
        setColour (Label::textColourId,                       Theme::textDim);
        setColour (Slider::textBoxTextColourId,               Theme::text);
        setColour (Slider::textBoxOutlineColourId,            Colours::transparentBlack);
        setColour (Slider::textBoxBackgroundColourId,         Colours::transparentBlack);
        setColour (Slider::textBoxHighlightColourId,          Theme::steel.withAlpha (0.5f));
        setColour (TextButton::textColourOffId,               Theme::text);
        setColour (TextButton::textColourOnId,                Theme::text);
    }

    juce::Font getLabelFont (juce::Label&) override           { return Theme::font (12.0f, true); }
    juce::Font getComboBoxFont (juce::ComboBox&) override     { return Theme::font (13.0f, true); }
    juce::Font getPopupMenuFont() override                    { return Theme::font (13.5f); }
    juce::Font getTextButtonFont (juce::TextButton&, int) override { return Theme::tracked (11.5f, true, 0.1f); }

    //--------------------------------------------------------------------------
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float pos,
                           float startAngle, float endAngle, juce::Slider& s) override
    {
        using namespace juce;

        const bool isMacro = (bool) s.getProperties().getWithDefault ("macro", false);
        const Colour c1 = isMacro ? Theme::silver : Theme::steel;
        const Colour c2 = isMacro ? Colours::white : Theme::ice;
        const bool hot  = s.isMouseOverOrDragging();
        const bool on   = s.isEnabled();

        if (! on)
            g.beginTransparencyLayer (0.35f);

        const auto bounds = Rectangle<float> ((float) x, (float) y, (float) width, (float) height).reduced (2.0f);
        const float radius = jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f;
        const auto centre  = bounds.getCentre();
        const float angle  = startAngle + pos * (endAngle - startAngle);

        auto dir = [] (float a) { return Point<float> (std::sin (a), -std::cos (a)); };

        // znaczniki skali
        constexpr int nTicks = 11;
        for (int i = 0; i < nTicks; ++i)
        {
            const float a = startAngle + (float) i / (float) (nTicks - 1) * (endAngle - startAngle);
            const bool end = (i == 0 || i == nTicks - 1);
            g.setColour (Theme::textDim.withAlpha (end ? 0.85f : 0.40f));
            g.drawLine (Line<float> (centre + dir (a) * (radius - 0.5f), centre + dir (a) * (radius - (end ? 5.0f : 3.5f))),
                        end ? 1.5f : 1.0f);
        }

        // tor i łuk wartości (zimne światło)
        const float arcR = radius - 9.0f;
        const float trackW = 2.6f;

        Path track;
        track.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, endAngle, true);
        g.setColour (Colours::black.withAlpha (0.8f));
        g.strokePath (track, PathStrokeType (trackW + 1.6f, PathStrokeType::curved, PathStrokeType::rounded));
        g.setColour (Colour (0xff222831));
        g.strokePath (track, PathStrokeType (trackW, PathStrokeType::curved, PathStrokeType::rounded));

        if (pos > 0.002f)
        {
            Path val;
            val.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, angle, true);

            g.setColour (c2.withAlpha (hot ? 0.28f : 0.16f));
            g.strokePath (val, PathStrokeType (trackW + 5.0f, PathStrokeType::curved, PathStrokeType::rounded));

            g.setGradientFill (ColourGradient (c1, centre.x - arcR, centre.y, c2, centre.x + arcR, centre.y, false));
            g.strokePath (val, PathStrokeType (trackW, PathStrokeType::curved, PathStrokeType::rounded));
        }

        // korpus: gładki otoczak
        const float bodyR = arcR - 6.0f;

        g.setGradientFill (ColourGradient (Colours::black.withAlpha (0.7f), centre.x, centre.y + 3.5f,
                                           Colours::black.withAlpha (0.0f),  centre.x + bodyR + 9.0f, centre.y + 3.5f, true));
        g.fillEllipse (centre.x - bodyR - 9.0f, centre.y - bodyR - 5.5f, (bodyR + 9.0f) * 2.0f, (bodyR + 9.0f) * 2.0f);

        g.setGradientFill (ColourGradient (Colour (0xff434a56), centre.x - bodyR * 0.65f, centre.y - bodyR * 0.9f,
                                           Colour (0xff0b0d10), centre.x + bodyR * 0.6f,  centre.y + bodyR,       false));
        g.fillEllipse (centre.x - bodyR, centre.y - bodyR, bodyR * 2.0f, bodyR * 2.0f);

        // odblask na górnej-lewej krawędzi (światło z góry, jak na kamieniach w logo)
        {
            Path rim;
            rim.addCentredArc (centre.x, centre.y, bodyR - 0.8f, bodyR - 0.8f, 0.0f,
                               MathConstants<float>::pi * 1.18f, MathConstants<float>::pi * 1.82f, true);
            g.setColour (Theme::ice.withAlpha (hot ? 0.75f : 0.5f));
            g.strokePath (rim, PathStrokeType (1.3f, PathStrokeType::curved, PathStrokeType::rounded));
        }

        // lekko wklęsła "twarz"
        const float faceR = bodyR - 4.5f;
        g.setGradientFill (ColourGradient (Colour (0xff12151a), centre.x - faceR * 0.4f, centre.y - faceR,
                                           Colour (0xff2b313b), centre.x + faceR * 0.4f, centre.y + faceR, false));
        g.fillEllipse (centre.x - faceR, centre.y - faceR, faceR * 2.0f, faceR * 2.0f);

        // wskaźnik = cienka szczelina światła
        const auto tip  = centre + dir (angle) * (faceR - 1.5f);
        const auto base = centre + dir (angle) * (faceR * 0.22f);
        g.setColour (c2.withAlpha (0.28f));
        g.drawLine (Line<float> (base, tip), 5.0f);
        g.setColour (Colours::white);
        g.drawLine (Line<float> (base, tip), 1.9f);

        if (! on)
            g.endTransparencyLayer();
    }

    //--------------------------------------------------------------------------
    void drawComboBox (juce::Graphics& g, int w, int h, bool, int, int, int, int, juce::ComboBox& box) override
    {
        using namespace juce;
        const auto r = Rectangle<float> (0.0f, 0.0f, (float) w, (float) h).reduced (0.5f);

        g.setGradientFill (ColourGradient (Colour (0xff20252d), 0.0f, 0.0f, Colour (0xff0e1115), 0.0f, (float) h, false));
        g.fillRoundedRectangle (r, 9.0f);

        const bool hot = box.isMouseOver (true) || box.isPopupActive();
        g.setColour (hot ? Theme::ice.withAlpha (0.8f) : Theme::stroke);
        g.drawRoundedRectangle (r, 9.0f, 1.0f);

        Path arrow;
        const float ax = (float) w - 15.0f, ay = (float) h * 0.5f;
        arrow.startNewSubPath (ax - 3.8f, ay - 2.0f);
        arrow.lineTo (ax, ay + 2.5f);
        arrow.lineTo (ax + 3.8f, ay - 2.0f);
        g.setColour (hot ? Theme::ice : Theme::textDim);
        g.strokePath (arrow, PathStrokeType (1.7f, PathStrokeType::curved, PathStrokeType::rounded));
    }

    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds (9, 1, box.getWidth() - 27, box.getHeight() - 2);
        label.setFont (getComboBoxFont (box));
        label.setJustificationType (juce::Justification::centredLeft);
    }

    //--------------------------------------------------------------------------
    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button, bool, bool) override
    {
        using namespace juce;
        const auto b = button.getLocalBounds().toFloat();
        const bool on = button.getToggleState();

        const float pw = 34.0f, ph = 18.0f;
        const Rectangle<float> pill (b.getX() + 1.0f, b.getCentreY() - ph * 0.5f, pw, ph);

        if (on)
        {
            g.setColour (Theme::ice.withAlpha (0.14f));
            g.fillRoundedRectangle (pill.expanded (2.5f), (ph + 5.0f) * 0.5f);
        }

        g.setColour (on ? Theme::steel.withAlpha (0.30f) : Colour (0xff0c0e12));
        g.fillRoundedRectangle (pill, ph * 0.5f);
        g.setColour (on ? Theme::ice : Theme::stroke);
        g.drawRoundedRectangle (pill, ph * 0.5f, 1.2f);

        const float tx = on ? pill.getRight() - ph + 3.0f : pill.getX() + 3.0f;
        g.setColour (Colours::black.withAlpha (0.5f));
        g.fillEllipse (tx, pill.getY() + 4.0f, ph - 6.0f, ph - 6.0f);
        g.setColour (on ? Colours::white : Theme::textDim);
        g.fillEllipse (tx, pill.getY() + 3.0f, ph - 6.0f, ph - 6.0f);

        g.setColour (on ? Theme::text : Theme::textDim);
        g.setFont (Theme::tracked (11.0f, true, 0.08f));
        g.drawText (button.getButtonText(), b.withTrimmedLeft (pw + 8.0f), Justification::centredLeft);
    }

    //--------------------------------------------------------------------------
    void drawButtonBackground (juce::Graphics& g, juce::Button& b, const juce::Colour&,
                               bool highlighted, bool down) override
    {
        using namespace juce;
        const auto r = b.getLocalBounds().toFloat().reduced (0.5f);

        g.setGradientFill (ColourGradient (Colour (down ? 0xff0e1115 : 0xff222831), 0.0f, r.getY(),
                                           Colour (0xff0e1115), 0.0f, r.getBottom(), false));
        g.fillRoundedRectangle (r, 9.0f);
        g.setColour (highlighted ? Theme::ice.withAlpha (0.8f) : Theme::stroke);
        g.drawRoundedRectangle (r, 9.0f, 1.0f);
    }
};
