/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "Delay.h"

#include <JuceHeader.h>
#include "PluginProcessor.h"

class JDelayLookAndFeel : public juce::LookAndFeel_V4
{
public:
    JDelayLookAndFeel()
    {
        setColour(juce::PopupMenu::ColourIds::textColourId, juce::Colours::white);
        setColour(juce::PopupMenu::ColourIds::backgroundColourId, juce::Colours::black);
        setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colours::black);
        setColour(juce::Slider::ColourIds::textBoxHighlightColourId, juce::Colours::darkgrey);
    }

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                          float sliderPosProportional, 
                          float rotaryStartAngle,
                          float rotaryEndAngle, 
                          juce::Slider&) override;

    void drawComboBox(juce::Graphics&, int width, int height, bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox&) override;

    juce::Font getComboBoxFont(juce::ComboBox&) override;

    void positionComboBoxText(juce::ComboBox&, juce::Label&) override;

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        const bool isSeparator, const bool isActive,
        const bool isHighlighted, const bool isTicked,
        const bool hasSubMenu, const juce::String& text,
        const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* const textColourToUse) override;

    void getIdealPopupMenuItemSize(const juce::String& text, const bool isSeparator,
        int standardMenuItemHeight, int& idealWidth, int& idealHeight) override;

private:

};

class JDelayDryLevelLookAndFeel : public JDelayLookAndFeel
{
public:

private:

};

class JDelayDelayTimeLookAndFeel : public JDelayLookAndFeel
{
public:

private:

};

class JDelayFeedbackLookAndFeel : public JDelayLookAndFeel
{
public:

private:

};

class JDelayRatioLookAndFeel : public JDelayLookAndFeel
{
public:

private:

};

//==============================================================================
class JDelayComboBox : public juce::ComboBox
{
public:
    JDelayComboBox() : juce::ComboBox()
    {
        setLookAndFeel(&lnf);
    }

    ~JDelayComboBox()
    {
        setLookAndFeel(nullptr);
    }


private:
    JDelayLookAndFeel lnf;
};

//==============================================================================
class JDelaySlider : public juce::Slider
{
public:
    JDelaySlider(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) : 
                           juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                        juce::Slider::TextEntryBoxPosition::TextBoxBelow),
                                        rangedAudioParam(&rap)
    {
        setLookAndFeel(&lnf);
    }

    ~JDelaySlider()
    {
        setLookAndFeel(nullptr);
    }

    struct RotarySliderLabelPosition
    {
        float rotarySliderLabelPos;
        juce::String rotarySliderLabelText;
    };

    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 14; }

private:
    JDelayLookAndFeel lnf;

    juce::RangedAudioParameter* rangedAudioParam;
};

//==============================================================================
class JDelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    JDelayAudioProcessorEditor(JDelayAudioProcessor&);
    ~JDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void createLabel(juce::Label& label, juce::String& text);
    void createLabels();

    // std::vector<juce::Component*> getJDelayComponents();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JDelayAudioProcessor& audioProcessor;

    JDelaySlider dryLevelSlider,
        delayTimeSlider,
        feedbackSlider, 
        ratioSlider,
        wetLevelSlider;

    JDelayDryLevelLookAndFeel dryLevelLnf;
    JDelayDelayTimeLookAndFeel delayTimeLnf;
    JDelayFeedbackLookAndFeel feedbackLnf;
    JDelayRatioLookAndFeel ratioLnf;

    JDelayComboBox delayTypeComboBox;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;

    SliderAttachment delayTimeSliderAttachment,
        feedbackSliderAttachment,
        ratioSliderAttachment,
        wetLevelSliderAttachment,
        dryLevelSliderAttachment;

    using ComboBoxAttachment = APVTS::ComboBoxAttachment;
    ComboBoxAttachment delayTypeComboBoxAttachment;

    juce::Label dryLevelLabel,
        delayTimeLabel,
        feedbackLabel,
        ratioLabel,
        wetLevelLabel,
        delayTypeLabel,
        dryLevelUnitsLabel,
        delayTimeUnitsLabel,
        feedbackUnitsLabel,
        ratioUnitsLabel,
        wetLevelUnitsLabel,
        delayTypeUnitsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JDelayAudioProcessorEditor)
};