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

    enum controlID
    {
        delayTime_mSec = 0,
        delayFeedback_Pct = 1,
        delayRatio_Pct = 2,
        delayType = 3,
        wetLevel_dB = 4,
        dryLevel_dB = 5
    };

private:
    void makeSlider(juce::Slider* slider, juce::String suffix, juce::Component* parent);

    void makeSliderLabel(juce::Label* label, juce::String labelText, juce::Slider& slider, juce::Component* parent);

    juce::Slider delayTimeSlider;
    juce::Label delayTimeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeSliderAttachment;

    juce::Slider feedbackSlider;
    juce::Label feedbackLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;

    juce::Slider ratioSlider;
    juce::Label ratioLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttachment;

    juce::Slider wetLevelSlider;
    juce::Label wetLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelSliderAttachment;

    juce::Slider dryLevelSlider;
    juce::Label dryLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryLevelSliderAttachment;

    juce::ComboBox delayTypeComboBox;
    juce::Label delayTypeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> delayTypeComboBoxAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JDelayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JDelayAudioProcessorEditor)
};