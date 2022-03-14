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

    auto controlArea = bounds.removeFromTop(bounds.getHeight() * JUCE_LIVE_CONSTANT(0.5));

    auto dryLevelSliderArea = bounds.removeFromLeft(JUCE_LIVE_CONSTANT(0));
    dryLevelSlider.setBounds(dryLevelSliderArea);

    //auto controlArea = bounds.removeFromTop(bounds.getHeight() * JUCE_LIVE_CONSTANT(0.0156399));

    //auto dryLevelSliderArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(0.19));
    //dryLevelSlider.setBounds(dryLevelSliderArea);

    //auto delayTypeButtonArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(0.1))
    //    .removeFromTop(bounds.getHeight() * JUCE_LIVE_CONSTANT(1.01611));
    //delayTypeButton.setBounds(delayTypeButtonArea);

    //auto delayTimeArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(0.26));
    //delayTimeSlider.setBounds(delayTimeArea);

    //auto feedbackArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(0.34));
    //feedbackSlider.setBounds(feedbackArea);

    //auto ratioArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(0.50));
    //ratioSlider.setBounds(ratioArea);

    //auto wetLevelSliderArea = bounds.removeFromLeft(bounds.getWidth() * JUCE_LIVE_CONSTANT(2.0));
    //wetLevelSlider.setBounds(wetLevelSliderArea);
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
        &delayTypeButton
    };
}