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
    makeSlider(&delayTimeSlider, " mSec", this);
    makeSliderLabel(&delayTimeLabel, "Delay Time", delayTimeSlider, this);

    delayTimeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "DELAY TIME", delayTimeSlider);

    //======================

    makeSlider(&feedbackSlider, " %", this);
    makeSliderLabel(&feedbackLabel, "Feedback", feedbackSlider, this);

    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "FEEDBACK", feedbackSlider);

    //======================

    // Is the ratio param for wet/dry mixing?
    makeSlider(&ratioSlider, " %", this);
    makeSliderLabel(&ratioLabel, "Ratio", ratioSlider, this);

    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "RATIO", ratioSlider);

    //======================

    makeSlider(&wetLevelSlider, " dB", this);
    makeSliderLabel(&wetLevelLabel, "Wet Level", wetLevelSlider, this);

    wetLevelSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
        "WETLEVEL", wetLevelSlider);

    //======================

    makeSlider(&dryLevelSlider, " dB", this);
    makeSliderLabel(&dryLevelLabel, "Dry Level", dryLevelSlider, this);

    dryLevelSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,
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

    delayTimeSlider.setBounds(getWidth() / 2 - 275, getHeight() / 2 - 150, 150, 100);
    feedbackSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 - 150, 150, 100);
    ratioSlider.setBounds(getWidth() / 2 + 125, getHeight() / 2 - 150, 150, 100);
    wetLevelSlider.setBounds(getWidth() / 2 - 275, getHeight() / 2 + 25, 150, 100);
    dryLevelSlider.setBounds(getWidth() / 2 - 75, getHeight() / 2 + 25, 150, 100);
    delayTypeComboBox.setBounds(getWidth() / 2 + 125, getHeight() / 2 + 25, 150, 50);
}

void JDelayAudioProcessorEditor::makeSlider(juce::Slider* slider, juce::String suffix, juce::Component* parent)
{
    slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    slider->setTextValueSuffix(suffix);
    addAndMakeVisible(slider);
}

void JDelayAudioProcessorEditor::makeSliderLabel(juce::Label* label, juce::String labelText, juce::Slider& slider, juce::Component* parent)
{
    label->setText(labelText, juce::dontSendNotification);
    label->attachToComponent(&slider, false);
    label->setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}