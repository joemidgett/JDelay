/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
JDelayAudioProcessorEditor::JDelayAudioProcessorEditor(JDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),

    dryLevelSlider(*audioProcessor.apvts.getParameter("DRYLEVEL"), "dB"),
    delayTimeSlider(*audioProcessor.apvts.getParameter("DELAYTIME"), "mSec"),
    feedbackSlider(*audioProcessor.apvts.getParameter("FEEDBACK"), "%"),
    ratioSlider(*audioProcessor.apvts.getParameter("RATIO"), "%"),
    wetLevelSlider(*audioProcessor.apvts.getParameter("WETLEVEL"), "dB"),

    dryLevelSliderAttachment(audioProcessor.apvts, "DRYLEVEL", dryLevelSlider),
    delayTimeSliderAttachment(audioProcessor.apvts, "DELAYTIME", delayTimeSlider),
    feedbackSliderAttachment(audioProcessor.apvts, "FEEDBACK", feedbackSlider),
    ratioSliderAttachment(audioProcessor.apvts, "RATIO", ratioSlider),
    wetLevelSliderAttachment(audioProcessor.apvts, "WETLEVEL", wetLevelSlider),
    delayTypeComboBoxAttachment(audioProcessor.apvts, "DELAYTYPE", delayTypeComboBox)
{
    createLabels();

    addAndMakeVisible(dryLevelSlider);
    dryLevelSlider.setLookAndFeel(&dryLevelLnf);

    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setLookAndFeel(&delayTimeLnf);

    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setLookAndFeel(&feedbackLnf);

    addAndMakeVisible(ratioSlider);
    ratioSlider.setLookAndFeel(&ratioLnf);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setLookAndFeel(&wetLevelLnf);

    addAndMakeVisible(delayTypeComboBox);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 180);
}

JDelayAudioProcessorEditor::~JDelayAudioProcessorEditor()
{
    dryLevelSlider.setLookAndFeel(nullptr);
    delayTimeSlider.setLookAndFeel(nullptr);
    feedbackSlider.setLookAndFeel(nullptr);
    ratioSlider.setLookAndFeel(nullptr);
    wetLevelSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void JDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
}

void JDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    auto dryLevelSliderArea = bounds.removeFromLeft(95).removeFromTop(140);
    dryLevelSlider.setBounds(dryLevelSliderArea);

    auto delayTimeArea = bounds.removeFromLeft(95).removeFromTop(140);
    delayTimeSlider.setBounds(delayTimeArea);

    auto feedbackArea = bounds.removeFromLeft(95).removeFromTop(140);
    feedbackSlider.setBounds(feedbackArea);

    auto ratioArea = bounds.removeFromLeft(95).removeFromTop(140);
    ratioSlider.setBounds(ratioArea);

    auto wetLevelSliderArea = bounds.removeFromLeft(95).removeFromTop(140);
    wetLevelSlider.setBounds(wetLevelSliderArea);

    auto delayTypeComboBoxArea = bounds.removeFromLeft(118).removeFromBottom(92).removeFromTop(25);
    delayTypeComboBox.addItem("Normal", 1);
    delayTypeComboBox.addItem("Ping Pong", 2);
    delayTypeComboBox.setSelectedItemIndex(0, juce::dontSendNotification);
    delayTypeComboBox.setJustificationType(juce::Justification::centred);
    delayTypeComboBox.setBounds(delayTypeComboBoxArea);

    dryLevelLabel.setBounds(-242, 5, getWidth() - 20, 30);
    delayTimeLabel.setBounds(-147, 5, getWidth() - 20, 30);
    feedbackLabel.setBounds(-52, 5, getWidth() - 20, 30);
    ratioLabel.setBounds(42, 5, getWidth() - 20, 30);
    wetLevelLabel.setBounds(138, 5, getWidth() - 20, 30);

    dryLevelUnitsLabel.setBounds(-242, 145, getWidth() - 20, 30);
    delayTimeUnitsLabel.setBounds(-147, 145, getWidth() - 20, 30);
    feedbackUnitsLabel.setBounds(-52, 145, getWidth() - 20, 30);
    ratioUnitsLabel.setBounds(42, 145, getWidth() - 20, 30);
    wetLevelUnitsLabel.setBounds(138, 145, getWidth() - 20, 30);
    
    delayTypeLabel.setBounds(242, 62, getWidth() - 20, 30);
}

void JDelayAudioProcessorEditor::createLabel(juce::Label& label, juce::String& text)
{
    addAndMakeVisible(label);
    label.setFont(juce::Font(14.0f));
    label.setText(text, juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
}

void JDelayAudioProcessorEditor::createLabels()
{
    createLabel(dryLevelLabel, juce::String("Dry Level"));
    createLabel(delayTimeLabel, juce::String("Delay Time"));
    createLabel(feedbackLabel, juce::String("Feedback"));
    createLabel(ratioLabel, juce::String("L/R Ratio"));
    createLabel(wetLevelLabel, juce::String("Wet Level"));
    createLabel(delayTypeLabel, juce::String("Delay Type"));

    createLabel(dryLevelUnitsLabel, juce::String("dB"));
    createLabel(delayTimeUnitsLabel, juce::String("mSec"));
    createLabel(feedbackUnitsLabel, juce::String("%"));
    createLabel(ratioUnitsLabel, juce::String("%"));
    createLabel(wetLevelUnitsLabel, juce::String("dB"));
}