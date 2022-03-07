/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JDelayAudioProcessorEditor::JDelayAudioProcessorEditor(JDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(delayTimeSlider);

    delayTimeLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeLabel.attachToComponent(&delayTimeSlider, false);
    delayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(delayTimeLabel);

    delayTimeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "DELAY TIME", delayTimeSlider);

    //======================

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(feedbackSlider);

    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(feedbackLabel);

    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "FEEDBACK", feedbackSlider);

    //======================

    ratioSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(ratioSlider);

    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.attachToComponent(&ratioSlider, false);
    ratioLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(ratioLabel);

    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "RATIO", ratioSlider);

    //======================

    wetLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(wetLevelSlider);

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.attachToComponent(&wetLevelSlider, false);
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetLevelLabel);

    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "WETLEVEL", wetLevelSlider);

    //======================

    dryLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    dryLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(dryLevelSlider);

    dryLevelLabel.setText("Dry Level", juce::dontSendNotification);
    dryLevelLabel.attachToComponent(&dryLevelSlider, false);
    dryLevelLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(dryLevelLabel);

    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "DRYLEVEL", dryLevelSlider);

    //======================

    delayTypeComboBox.addItem("Normal", 1);
    delayTypeComboBox.addItem("PingPong", 2);
    delayTypeComboBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(delayTypeComboBox);

    delayTypeLabel.setText("Delay Type", juce::dontSendNotification);
    delayTypeLabel.attachToComponent(&delayTypeComboBox, false);
    delayTypeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(delayTypeLabel);

    delayTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts,
        "DELAYTYPE", delayTypeComboBox);

    //======================

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 400);
}

JDelayAudioProcessorEditor::~JDelayAudioProcessorEditor()
{
}

//==============================================================================
void JDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void JDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();

    delayTimeSlider.setBounds(getWidth() / 2 - 275, getHeight() / 2 - 150, 150, 100);
    feedbackSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 - 150, 150, 100);
    ratioSlider.setBounds(getWidth() / 2 + 125, getHeight() / 2 - 150, 150, 100);
    wetLevelSlider.setBounds(getWidth() / 2 - 275, getHeight() / 2 + 25, 150, 100);
    dryLevelSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 + 25, 150, 100);
    delayTypeComboBox.setBounds(getWidth() / 2 + 125, getHeight() / 2 + 25, 150, 50);
}