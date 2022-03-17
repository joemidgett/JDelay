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
    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                          float sliderPosProportional, 
                          float rotaryStartAngle,
                          float rotaryEndAngle, 
                          juce::Slider&) override;

    void drawComboBox(juce::Graphics&, int width, int height, bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox&) override;
private:

};

class JDelayComboBox : public juce::ComboBox
{
public:
    JDelayComboBox()
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
class RotarySliderWithLabels : public juce::Slider
{
public:
    RotarySliderWithLabels(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) : 
                           juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                        juce::Slider::TextEntryBoxPosition::TextBoxBelow),
                                        rangedAudioParam(&rap)
    {
        setLookAndFeel(&lnf);
    }

    ~RotarySliderWithLabels()
    {
        setLookAndFeel(nullptr);
    }

    struct RotarySliderLabelPosition
    {
        float rotarySliderLabelPos;
        juce::String rotarySliderLabelText;
    };

    juce::Array<RotarySliderLabelPosition> labels;

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

    std::vector<juce::Component*> getJDelayComponents();

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JDelayAudioProcessor& audioProcessor;

    RotarySliderWithLabels delayTimeSlider, 
        feedbackSlider, 
        ratioSlider,
        wetLevelSlider, 
        dryLevelSlider;

    juce::ComboBox delayTypeComboBox;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;

    SliderAttachment delayTimeSliderAttachment,
        feedbackSliderAttachment,
        ratioSliderAttachment,
        wetLevelSliderAttachment,
        dryLevelSliderAttachment;

    using ComboBoxAttachment = APVTS::ComboBoxAttachment;

    ComboBoxAttachment delayTypeComboBoxAttachment;

    juce::Label delayTimeUnitsLabel, 
        feedbackUnitsLabel, 
        ratioUnitsLabel,
        wetLevelUnitsLabel, 
        dryLevelUnitsLabel, 
        delayTypeUnitsLabel;

    // JDelayLookAndFeel lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JDelayAudioProcessorEditor)
};