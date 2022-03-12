/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "Delay.h"

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class JDelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    JDelayAudioProcessorEditor(JDelayAudioProcessor&);
    ~JDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void makeSlider(juce::Slider* slider, juce::String suffix, juce::Component* parent);
    void makeSliderLabel(juce::Label* label, juce::String labelText, juce::Slider& slider, juce::Component* parent);

private:

    juce::Slider delayTimeSlider, feedbackSlider, ratioSlider,
        wetLevelSlider, dryLevelSlider;

    juce::ComboBox delayTypeComboBox;

    juce::Label delayTimeLabel, feedbackLabel, ratioLabel,
        wetLevelLabel, dryLevelLabel, delayTypeLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> delayTimeSliderAttachment,
        feedbackSliderAttachment,
        ratioSliderAttachment,
        wetLevelSliderAttachment,
        dryLevelSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> delayTypeComboBoxAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JDelayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JDelayAudioProcessorEditor)
};