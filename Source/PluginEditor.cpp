#include "PluginEditor.h"
#include "Parameters.h"
#include <BinaryData.h>

namespace
{
    // Odcina z lewej strony prostokąta kolumnę o szerokości w, a potem odstęp.
    juce::Rectangle<int> takeLeft (juce::Rectangle<int>& row, int w, int gap)
    {
        auto r = row.removeFromLeft (w);
        row.removeFromLeft (gap);
        return r;
    }
}

//==============================================================================
BassoraAudioProcessorEditor::BassoraAudioProcessorEditor (BassoraAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p),
      scope (p),
      envEditor (p.apvts),
      filterPad (p.apvts),
      eqPad (p),
      compDisplay (p)
{
    setLookAndFeel (&laf);

    addAndMakeVisible (ui);
    ui.setBounds (0, 0, baseW, baseH);

    // --- ekrany ---
    ui.addAndMakeVisible (scope);
    ui.addAndMakeVisible (envEditor);
    ui.addAndMakeVisible (filterPad);
    ui.addAndMakeVisible (eqPad);
    ui.addAndMakeVisible (compDisplay);

    // --- listy wyboru i przełączniki ---
    addCombo (wave1Box,     Choices::waveNames(),       IDs::wave);
    addCombo (wave2Box,     Choices::waveNames(),       IDs::wave2);
    addCombo (lfoShapeBox,  Choices::lfoShapeNames(),   IDs::lfoShape);
    addCombo (lfoTargetBox, Choices::lfoTargetNames(),  IDs::lfoTarget);
    addCombo (lfoSyncBox,   Choices::lfoSyncNames(),    IDs::lfoSync);
    addCombo (driveTypeBox, { "Soft", "Hard", "Fold" }, IDs::driveType);

    addToggle (legatoButton, IDs::legato, legatoAttachment);
    addToggle (eqToggle,     IDs::eqOn,   eqAttachment);
    addToggle (compToggle,   IDs::compOn, compAttachment);

    lfoSyncBox.onChange = [this] { updateLfoRateEnabled(); };

    // --- grupy (kolejność = kolejność w layoutUi) ---
    // rząd A: ekrany
    groups.push_back ({ "Output",          Theme::ice,  {}, {}, &scope });
    groups.push_back ({ "Amp envelope",    Theme::steel, {}, {}, &envEditor });
    groups.push_back ({ "Filter",          Theme::aqua,   {}, {}, &filterPad });

    // rząd B: źródła dźwięku
    groups.push_back ({ "Oscillator 1", Theme::ice, { &wave1Box },
                        { &addKnob ("Morph", IDs::wtPos), &addKnob ("Tune", IDs::tune),
                          &addKnob ("Sub", IDs::sub), &addKnob ("Click", IDs::click) } });

    groups.push_back ({ "Oscillator 2", Theme::ice, { &wave2Box },
                        { &addKnob ("Morph", IDs::wtPos2), &addKnob ("Tune", IDs::semis2),
                          &addKnob ("Detune", IDs::detune2), &addKnob ("Level", IDs::level2) } });

    groups.push_back ({ "Pitch & glide", Theme::steel, { &legatoButton },
                        { &addKnob ("Pitch env", IDs::pitchAmt), &addKnob ("Time", IDs::pitchTime),
                          &addKnob ("Glide", IDs::glide) } });

    {
        auto& rate  = addKnob ("Rate", IDs::lfoRate);
        auto& depth = addKnob ("Depth", IDs::lfoDepth);
        lfoRateKnob = &rate;
        groups.push_back ({ "LFO", Theme::aqua, { &lfoShapeBox, &lfoTargetBox, &lfoSyncBox }, { &rate, &depth } });
    }

    // rząd C
    groups.push_back ({ "Amp", Theme::steel, {},
                        { &addKnob ("Attack", IDs::attack), &addKnob ("Decay", IDs::decay),
                          &addKnob ("Sustain", IDs::sustain), &addKnob ("Release", IDs::release) } });

    groups.push_back ({ "Drive, filter & output", Theme::aqua, { &driveTypeBox },
                        { &addKnob ("Drive", IDs::drive), &addKnob ("Cutoff", IDs::cutoff),
                          &addKnob ("Reso", IDs::reso), &addKnob ("Gain", IDs::gain) } });

    groups.push_back ({ "Macros", Theme::silver, {},
                        { &addKnob ("Punch", IDs::macro1, true), &addKnob ("Dirt", IDs::macro2, true),
                          &addKnob ("Length", IDs::macro3, true), &addKnob ("Tone", IDs::macro4, true) } });

    // rząd D: efekty końcowe
    groups.push_back ({ "Equalizer", Theme::ice, {}, { &addKnob ("Mid Q", IDs::eqMidQ) }, &eqPad, 360, &eqToggle });

    groups.push_back ({ "Compressor", Theme::steel, {},
                        { &addKnob ("Thresh", IDs::compThresh), &addKnob ("Ratio", IDs::compRatio),
                          &addKnob ("Attack", IDs::compAttack), &addKnob ("Release", IDs::compRelease),
                          &addKnob ("Makeup", IDs::compMakeup), &addKnob ("Mix", IDs::compMix) },
                        &compDisplay, 230, &compToggle });

    // --- przeglądarka presetów ---
    presetBox.setTextWhenNothingSelected ("Custom");
    presetBox.onChange = [this]
    {
        const int idx = presetBox.getSelectedId() - 1;
        if (idx >= 0)
            audioProcessor.loadPreset (idx);
        syncPresetSelection();
    };

    ui.addAndMakeVisible (presetBox);
    ui.addAndMakeVisible (prevBtn);
    ui.addAndMakeVisible (nextBtn);
    ui.addAndMakeVisible (saveBtn);
    ui.addAndMakeVisible (deleteBtn);

    prevBtn.onClick   = [this] { stepPreset (-1); };
    nextBtn.onClick   = [this] { stepPreset (+1); };
    saveBtn.onClick   = [this] { showSaveDialog(); };
    deleteBtn.onClick = [this] { confirmDelete(); };

    audioProcessor.refreshPresetList();
    rebuildPresetMenu();
    updateLfoRateEnabled();

    layoutUi();
    rebuildBackground();

    // okno o zmiennym rozmiarze (zachowuje proporcje); rozmiar jest zapamiętywany w stanie wtyczki
    setResizable (true, true);
    setResizeLimits (baseW * 6 / 10, baseH * 6 / 10, baseW * 3 / 2, baseH * 3 / 2);
    if (auto* c = getConstrainer())
        c->setFixedAspectRatio ((double) baseW / (double) baseH);

    const int savedW = juce::jlimit (baseW * 6 / 10, baseW * 3 / 2,
                                     (int) audioProcessor.apvts.state.getProperty ("uiWidth", baseW));
    setSize (savedW, (int) std::lround ((double) savedW * baseH / baseW));

    startTimerHz (4);
}

BassoraAudioProcessorEditor::~BassoraAudioProcessorEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
}

//==============================================================================
BassoraAudioProcessorEditor::Knob& BassoraAudioProcessorEditor::addKnob (const juce::String& name,
                                                                         const char* paramID, bool macro)
{
    auto k = std::make_unique<Knob>();

    k->slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 66, 16);
    k->slider.getProperties().set ("macro", macro);

    k->label.setText (name, juce::dontSendNotification);
    k->label.setJustificationType (juce::Justification::centred);
    k->label.setColour (juce::Label::textColourId, Theme::textDim);

    ui.addAndMakeVisible (k->slider);
    ui.addAndMakeVisible (k->label);

    k->attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.apvts, paramID, k->slider);

    knobs.push_back (std::move (k));
    return *knobs.back();
}

void BassoraAudioProcessorEditor::addCombo (juce::ComboBox& box, const juce::StringArray& items, const char* paramID)
{
    box.addItemList (items, 1);
    ui.addAndMakeVisible (box);
    comboAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        audioProcessor.apvts, paramID, box));
}

void BassoraAudioProcessorEditor::addToggle (juce::ToggleButton& button, const char* paramID,
                                             std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>& attachment)
{
    ui.addAndMakeVisible (button);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (
        audioProcessor.apvts, paramID, button);
}

void BassoraAudioProcessorEditor::updateLfoRateEnabled()
{
    if (lfoRateKnob == nullptr)
        return;

    const bool free = lfoSyncBox.getSelectedItemIndex() <= 0;
    if (lfoRateKnob->slider.isEnabled() != free)
    {
        lfoRateKnob->slider.setEnabled (free);          // przy synchronizacji tempo wyznacza host
        lfoRateKnob->label.setAlpha (free ? 1.0f : 0.4f);
    }
}

//==============================================================================
// Presety
//==============================================================================
void BassoraAudioProcessorEditor::rebuildPresetMenu()
{
    presetBox.clear (juce::dontSendNotification);

    const auto& list = audioProcessor.getPresetList();
    auto* root = presetBox.getRootMenu();

    // kolejne wpisy tej samej kategorii trafiają do jednego podmenu
    juce::PopupMenu sub;
    juce::String currentCategory;

    auto flush = [&]
    {
        if (currentCategory.isNotEmpty())
            root->addSubMenu (currentCategory, sub);
        sub = juce::PopupMenu();
    };

    for (size_t i = 0; i < list.size(); ++i)
    {
        if (list[i].category != currentCategory)
        {
            flush();
            currentCategory = list[i].category;
        }
        sub.addItem ((int) i + 1, list[i].name);
    }
    flush();

    syncPresetSelection();
}

void BassoraAudioProcessorEditor::syncPresetSelection()
{
    const int idx = audioProcessor.getCurrentPresetIndex();
    presetBox.setSelectedId (idx >= 0 ? idx + 1 : 0, juce::dontSendNotification);

    const auto& list = audioProcessor.getPresetList();
    deleteBtn.setEnabled (idx >= 0 && ! list[(size_t) idx].factory);
}

void BassoraAudioProcessorEditor::stepPreset (int dir)
{
    const int n = (int) audioProcessor.getPresetList().size();
    if (n == 0)
        return;

    const int cur = audioProcessor.getCurrentPresetIndex();
    const int next = cur < 0 ? (dir > 0 ? 0 : n - 1) : (cur + dir + n) % n;
    audioProcessor.loadPreset (next);
    syncPresetSelection();
}

void BassoraAudioProcessorEditor::showSaveDialog()
{
    auto* w = new juce::AlertWindow ("Save preset", "Name your preset. It will appear under \"My presets\".",
                                     juce::MessageBoxIconType::NoIcon, this);
    w->addTextEditor ("name", audioProcessor.getCurrentPresetName(), "Name:");
    w->addButton ("Save",   1, juce::KeyPress (juce::KeyPress::returnKey));
    w->addButton ("Cancel", 0, juce::KeyPress (juce::KeyPress::escapeKey));

    juce::Component::SafePointer<BassoraAudioProcessorEditor> safe (this);

    w->enterModalState (true,
                        juce::ModalCallbackFunction::create ([safe, w] (int result)
                        {
                            if (safe != nullptr && result == 1)
                                safe->commitSave (w->getTextEditorContents ("name"));
                        }),
                        true);
}

void BassoraAudioProcessorEditor::commitSave (const juce::String& rawName)
{
    const auto name = rawName.trim();
    if (name.isEmpty())
        return;

    juce::Component::SafePointer<BassoraAudioProcessorEditor> safe (this);

    auto doSave = [safe, name]
    {
        if (safe == nullptr)
            return;

        if (safe->audioProcessor.saveUserPreset (name, true))
            safe->rebuildPresetMenu();
        else
            juce::AlertWindow::showMessageBoxAsync (juce::MessageBoxIconType::WarningIcon, "Could not save preset",
                                                    "The preset file could not be written to:\n"
                                                        + BassoraAudioProcessor::getUserPresetDirectory().getFullPathName());
    };

    if (audioProcessor.userPresetExists (name))
    {
        juce::AlertWindow::showAsync (juce::MessageBoxOptions::makeOptionsOkCancel (
                                          juce::MessageBoxIconType::QuestionIcon, "Overwrite preset?",
                                          "A preset called \"" + name + "\" already exists. Replace it?",
                                          "Replace", "Cancel", this),
                                      [doSave] (int result) { if (result == 1) doSave(); });
    }
    else
    {
        doSave();
    }
}

void BassoraAudioProcessorEditor::confirmDelete()
{
    const int idx = audioProcessor.getCurrentPresetIndex();
    const auto& list = audioProcessor.getPresetList();
    if (idx < 0 || list[(size_t) idx].factory)
        return;

    juce::Component::SafePointer<BassoraAudioProcessorEditor> safe (this);

    juce::AlertWindow::showAsync (juce::MessageBoxOptions::makeOptionsOkCancel (
                                      juce::MessageBoxIconType::QuestionIcon, "Delete preset?",
                                      "Delete \"" + list[(size_t) idx].name + "\"? This cannot be undone.",
                                      "Delete", "Cancel", this),
                                  [safe, idx] (int result)
                                  {
                                      if (safe != nullptr && result == 1)
                                      {
                                          safe->audioProcessor.deleteUserPreset (idx);
                                          safe->rebuildPresetMenu();
                                      }
                                  });
}

void BassoraAudioProcessorEditor::timerCallback()
{
    // preset mógł zostać zmieniony z zewnątrz (host, program change)
    if (! presetBox.isPopupActive())
        syncPresetSelection();

    updateLfoRateEnabled();
}

//==============================================================================
void BassoraAudioProcessorEditor::rebuildBackground()
{
    constexpr float scale = 2.0f;      // rysujemy w 2x, żeby było ostro na ekranach HiDPI
    ui.background = juce::Image (juce::Image::ARGB, (int) ((float) baseW * scale), (int) ((float) baseH * scale), true);

    juce::Graphics g (ui.background);
    g.addTransform (juce::AffineTransform::scale (scale));
    g.setImageResamplingQuality (juce::Graphics::highResamplingQuality);

    const float fw = (float) baseW, fh = (float) baseH;

    // tło: głęboka czerń z chłodną poświatą za emblematem i winietą
    g.setGradientFill (juce::ColourGradient (juce::Colour (0xff090b10), 0.0f, 0.0f,
                                             juce::Colour (0xff020203), fw, fh, false));
    g.fillAll();

    g.setGradientFill (juce::ColourGradient (Theme::ice.withAlpha (0.13f), 62.0f, 52.0f,
                                             Theme::ice.withAlpha (0.0f),  62.0f, 420.0f, true));
    g.fillRect (0.0f, 0.0f, fw, fh);

    g.setGradientFill (juce::ColourGradient (Theme::steel.withAlpha (0.06f), fw * 0.8f, fh + 40.0f,
                                             Theme::steel.withAlpha (0.0f),  fw * 0.8f, fh - 460.0f, true));
    g.fillRect (0.0f, 0.0f, fw, fh);

    g.setGradientFill (juce::ColourGradient (juce::Colours::transparentBlack, fw * 0.5f, fh * 0.5f,
                                             juce::Colours::black.withAlpha (0.5f), 0.0f, 0.0f, true));
    g.fillRect (0.0f, 0.0f, fw, fh);

    // logo: emblemat + napis (z przezroczystych PNG wyciętych z grafiki marki) + podtytuł
    const auto emblem   = juce::ImageCache::getFromMemory (BinaryData::emblem_png,   BinaryData::emblem_pngSize);
    const auto wordmark = juce::ImageCache::getFromMemory (BinaryData::wordmark_png, BinaryData::wordmark_pngSize);

    if (emblem.isValid())
        g.drawImage (emblem, juce::Rectangle<float> (22.0f, 14.0f, 84.0f, 77.0f), juce::RectanglePlacement::centred);

    if (wordmark.isValid())
        g.drawImage (wordmark, juce::Rectangle<float> (118.0f, 26.0f, 300.0f, 36.2f), juce::RectanglePlacement::centred);

    g.setColour (Theme::textDim);
    g.setFont (Theme::tracked (10.5f, false, 0.34f));
    g.drawText ("808 & BASS GENERATOR", 122, 66, 300, 14, juce::Justification::centredLeft);

    // panele
    for (const auto& grp : groups)
        Theme::drawPanel (g, grp.bounds.toFloat(), grp.title, grp.accent);

    // delikatne ziarno (jak faktura kamienia) na całości
    juce::Image grain (juce::Image::ARGB, 256, 256, true);
    juce::Random rnd (1234);
    for (int y = 0; y < 256; ++y)
        for (int x = 0; x < 256; ++x)
        {
            const float a = rnd.nextFloat() * 0.06f;
            grain.setPixelAt (x, y, rnd.nextBool() ? juce::Colours::white.withAlpha (a)
                                                   : juce::Colours::black.withAlpha (a * 1.5f));
        }
    g.setTiledImageFill (grain, 0, 0, 1.0f);
    g.fillAll();
}

void BassoraAudioProcessorEditor::layoutUi()
{
    auto area = juce::Rectangle<int> (0, 0, baseW, baseH).reduced (20);

    // nagłówek: [<] [lista presetów] [>]   [Save] [Delete]
    auto header = area.removeFromTop (76);
    deleteBtn.setBounds (header.removeFromRight (70).withSizeKeepingCentre (70, 32));
    header.removeFromRight (6);
    saveBtn.setBounds (header.removeFromRight (64).withSizeKeepingCentre (64, 32));
    header.removeFromRight (16);
    nextBtn.setBounds (header.removeFromRight (32).withSizeKeepingCentre (32, 32));
    header.removeFromRight (6);
    presetBox.setBounds (header.removeFromRight (250).withSizeKeepingCentre (250, 32));
    header.removeFromRight (6);
    prevBtn.setBounds (header.removeFromRight (32).withSizeKeepingCentre (32, 32));
    area.removeFromTop (6);

    const int gap = 14;

    auto rowA = area.removeFromTop (200);
    area.removeFromTop (gap);
    auto rowB = area.removeFromTop (206);
    area.removeFromTop (gap);
    auto rowC = area.removeFromTop (176);
    area.removeFromTop (gap);
    auto rowD = area;

    // rząd A: scope | edytor obwiedni | filtr
    groups[0].bounds = takeLeft (rowA, 330, gap);
    groups[1].bounds = takeLeft (rowA, 430, gap);
    groups[2].bounds = rowA;

    // rząd B: osc1 | osc2 | pitch | lfo
    groups[3].bounds = takeLeft (rowB, 290, gap);
    groups[4].bounds = takeLeft (rowB, 290, gap);
    groups[5].bounds = takeLeft (rowB, 250, gap);
    groups[6].bounds = rowB;

    // rząd C: amp | drive+filtr | makra
    groups[7].bounds = takeLeft (rowC, 340, gap);
    groups[8].bounds = takeLeft (rowC, 400, gap);
    groups[9].bounds = rowC;

    // rząd D: EQ | kompresor
    groups[10].bounds = takeLeft (rowD, 500, gap);
    groups[11].bounds = rowD;

    for (auto& grp : groups)
    {
        auto inner = grp.bounds.reduced (12, 10);
        inner.removeFromTop (30);                                   // tytuł

        if (grp.headerWidget != nullptr)
            grp.headerWidget->setBounds (grp.bounds.getRight() - 12 - 66, grp.bounds.getY() + 11, 66, 22);

        if (grp.content != nullptr)
        {
            if (grp.knobs.empty())
            {
                grp.content->setBounds (inner.reduced (2, 2));
                continue;
            }

            grp.content->setBounds (inner.removeFromLeft (grp.contentWidth).reduced (2, 2));
            inner.removeFromLeft (8);
        }
        else if (! grp.extras.empty())
        {
            auto row = inner.removeFromTop (28);
            const int n = (int) grp.extras.size();
            const int w = row.getWidth() / n;
            for (auto* e : grp.extras)
                e->setBounds (row.removeFromLeft (w).reduced (n > 1 ? 3 : 0, 0));
            inner.removeFromTop (4);
        }

        if (! grp.knobs.empty())
        {
            const int w = inner.getWidth() / (int) grp.knobs.size();
            for (auto* k : grp.knobs)
            {
                auto cell = inner.removeFromLeft (w);
                k->label.setBounds (cell.removeFromTop (16));
                k->slider.setBounds (cell);
            }
        }
    }
}

void BassoraAudioProcessorEditor::resized()
{
    const int w = getWidth();
    if (w <= 0)
        return;

    ui.setTransform (juce::AffineTransform::scale ((float) w / (float) baseW));
    audioProcessor.apvts.state.setProperty ("uiWidth", w, nullptr);
}
