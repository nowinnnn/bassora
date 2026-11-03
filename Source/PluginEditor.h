#pragma once

#include "PluginProcessor.h"
#include "Theme.h"
#include "Widgets.h"

class BassoraAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit BassoraAudioProcessorEditor (BassoraAudioProcessor&);
    ~BassoraAudioProcessorEditor() override;

    void paint (juce::Graphics&) override {}
    void resized() override;

private:
    // Wszystkie kontrolki żyją na płótnie o stałym rozmiarze bazowym, które jest skalowane
    // transformacją - dzięki temu okno można płynnie powiększać i zmniejszać.
    struct Canvas : public juce::Component
    {
        void paint (juce::Graphics& g) override
        {
            if (background.isValid())
                g.drawImage (background, getLocalBounds().toFloat());
        }
        juce::Image background;
    };

    struct Knob
    {
        juce::Slider slider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
        juce::Label label;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    };

    struct Group
    {
        juce::String title;
        juce::Colour accent;
        std::vector<juce::Component*> extras;     // listy wyboru / przełączniki nad gałkami
        std::vector<Knob*> knobs;
        juce::Component* content = nullptr;       // ekran (scope, wykresy)
        int contentWidth = 0;                     // gdy są też gałki: szerokość ekranu po lewej
        juce::Component* headerWidget = nullptr;  // np. przełącznik On w rogu panelu
        juce::Rectangle<int> bounds;
    };

    Knob& addKnob (const juce::String& name, const char* paramID, bool macro = false);
    void addCombo (juce::ComboBox& box, const juce::StringArray& items, const char* paramID);
    void addToggle (juce::ToggleButton& button, const char* paramID,
                    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>& attachment);

    void layoutUi();
    void rebuildBackground();
    void timerCallback() override;

    // presety
    void rebuildPresetMenu();
    void syncPresetSelection();
    void stepPreset (int dir);
    void showSaveDialog();
    void commitSave (const juce::String& name);
    void confirmDelete();
    void updateLfoRateEnabled();

    static constexpr int baseW = 1200;
    static constexpr int baseH = 922;

    BassoraAudioProcessor& audioProcessor;

    AnalogLookAndFeel laf;      // własny LookAndFeel (nie ruszamy globalnego)
    Canvas ui;

    juce::ComboBox presetBox, wave1Box, wave2Box, lfoShapeBox, lfoTargetBox, lfoSyncBox, driveTypeBox;
    juce::TextButton prevBtn { "<" }, nextBtn { ">" }, saveBtn { "Save" }, deleteBtn { "Delete" };
    juce::ToggleButton legatoButton { "Legato" }, eqToggle { "On" }, compToggle { "On" };

    ScopeDisplay scope;
    EnvelopeEditor envEditor;
    FilterPad filterPad;
    EqPad eqPad;
    CompDisplay compDisplay;

    std::vector<std::unique_ptr<Knob>> knobs;
    std::vector<Group> groups;
    Knob* lfoRateKnob = nullptr;

    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> comboAttachments;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> legatoAttachment, eqAttachment, compAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassoraAudioProcessorEditor)
};
