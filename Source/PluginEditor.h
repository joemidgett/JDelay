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
                          juce::Slider&) override { };
private:

};

class RotarySliderWithLabels : public juce::Slider
{
public:
    RotarySliderWithLabels(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) : 
                           juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                        juce::Slider::TextEntryBoxPosition::TextBoxBelow),
                                        rangedAudioParam(&rap),
                                        suffix(unitSuffix)
    {
        setLookAndFeel(&lnf);
    }

    ~RotarySliderWithLabels()
    {
        setLookAndFeel(nullptr);
    }

    void paint(juce::Graphics& g) override { };
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 14; }
    juce::String getDisplayString() const;

private:
    JDelayLookAndFeel lnf;

    juce::RangedAudioParameter* rangedAudioParam;
    juce::String suffix;
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

    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> delayTypeComboBoxAttachment;

    //juce::Label delayTimeLabel, feedbackLabel, ratioLabel,
    //    wetLevelLabel, dryLevelLabel, delayTypeLabel;

    // JDelayLookAndFeel lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JDelayAudioProcessorEditor)
};