/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JDelayAudioProcessorEditor::JDelayAudioProcessorEditor(JDelayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    dryLevelSliderAttachment(audioProcessor.apvts, "DRYLEVEL", dryLevelSlider),
    delayTimeSliderAttachment(audioProcessor.apvts, "DELAYTIME", delayTimeSlider),
    feedbackSliderAttachment(audioProcessor.apvts, "FEEDBACK", feedbackSlider),
    ratioSliderAttachment(audioProcessor.apvts, "RATIO", ratioSlider),
    wetLevelSliderAttachment(audioProcessor.apvts, "WETLEVEL", wetLevelSlider),
    delayTypeComboBoxAttachment(audioProcessor.apvts, "DELAYTYPE", delayTypeComboBox)
{
    for (auto* comp : getJDelayComponents())
    {
        addAndMakeVisible(comp);
    }

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 200);
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

    auto dryLevelSliderArea = bounds.removeFromLeft(95);
    dryLevelSlider.setBounds(dryLevelSliderArea);

    auto delayTimeArea = bounds.removeFromLeft(95);
    delayTimeSlider.setBounds(delayTimeArea);

    auto feedbackArea = bounds.removeFromLeft(95);
    feedbackSlider.setBounds(feedbackArea);

    auto ratioArea = bounds.removeFromLeft(95);
    ratioSlider.setBounds(ratioArea);

    auto wetLevelSliderArea = bounds.removeFromLeft(95);
    wetLevelSlider.setBounds(wetLevelSliderArea);

    auto delayTypeComboBoxArea = bounds.removeFromLeft(115).removeFromBottom(125).removeFromTop(45);
    delayTypeComboBox.addItem("Normal", 1);
    delayTypeComboBox.addItem("Ping Pong", 2);
    delayTypeComboBox.setJustificationType(juce::Justification::centred);
    delayTypeComboBox.setBounds(delayTypeComboBoxArea);
}

std::vector<juce::Component*> JDelayAudioProcessorEditor::getJDelayComponents()
{
    return
    {
        &delayTimeSlider,
        &feedbackSlider,
        &ratioSlider,
        &wetLevelSlider,
        &dryLevelSlider,
        &delayTypeComboBox
    };
}