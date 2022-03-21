/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "./AudioDelay.h"
#include "./JDelayComboBox.h"
#include "./JDelayDelayTimeLookAndFeel.h"
#include "./JDelayDryLevelLookAndFeel.h"
#include "./JDelayFeedbackLookAndFeel.h"
#include "./JDelayRatioLookAndFeel.h"
#include "./JDelaySlider.h"
#include "./JDelayWetLevelLookAndFeel.h"
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

    void createLabel(juce::Label& label, juce::String& text);
    void createLabels();

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
    JDelayWetLevelLookAndFeel wetLevelLnf;

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