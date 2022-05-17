/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DSP/AudioDelay.h"
#include "GUI/JDelayComboBox.h"
#include "GUI/JDelayDelayTimeLookAndFeel.h"
#include "GUI/JDelayDryLevelLookAndFeel.h"
#include "GUI/JDelayFeedbackLookAndFeel.h"
#include "GUI/JDelayRatioLookAndFeel.h"
#include "GUI/JDelaySlider.h"
#include "GUI/JDelayWetLevelLookAndFeel.h"
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

    JDelayLookAndFeel jDelayLnf;

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
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SliderAttachment delayTimeSliderAttachment,
                     feedbackSliderAttachment,
                     ratioSliderAttachment,
                     wetLevelSliderAttachment,
                     dryLevelSliderAttachment;

    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
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