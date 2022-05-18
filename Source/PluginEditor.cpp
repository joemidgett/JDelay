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
    juce::LookAndFeel::setDefaultLookAndFeel(&jDelayLnf);

    createDelayTypeComboBox();
    createLabels();

    dryLevelSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::white);
    dryLevelSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::black);

    addAndMakeVisible(dryLevelSlider);
    addAndMakeVisible(delayTimeSlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(ratioSlider);
    addAndMakeVisible(wetLevelSlider);
    addAndMakeVisible(delayTypeComboBox);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(635, 190);
}

JDelayAudioProcessorEditor::~JDelayAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void JDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void JDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    dryLevelSlider.setBounds(0, 0, 103, 150);
    delayTimeSlider.setBounds(dryLevelSlider.getBounds().withX(dryLevelSlider.getRight()));
    feedbackSlider.setBounds(delayTimeSlider.getBounds().withX(delayTimeSlider.getRight()));
    ratioSlider.setBounds(feedbackSlider.getBounds().withX(feedbackSlider.getRight()));
    wetLevelSlider.setBounds(ratioSlider.getBounds().withX(ratioSlider.getRight()));
    delayTypeComboBox.setBounds(wetLevelSlider.getBounds()
                                              .withX(wetLevelSlider.getRight() + 3)
                                              .withY(wetLevelSlider.getY() + 90)
                                              .withHeight(wetLevelSlider.getHeight() - 130)
                                              .withWidth(wetLevelSlider.getWidth()));

    dryLevelLabel.setBounds(0, 5, 103, 30);
    delayTimeLabel.setBounds(dryLevelLabel.getBounds().withX(dryLevelLabel.getRight()));
    feedbackLabel.setBounds(delayTimeLabel.getBounds().withX(delayTimeLabel.getRight()));
    ratioLabel.setBounds(feedbackLabel.getBounds().withX(feedbackLabel.getRight()));
    wetLevelLabel.setBounds(ratioLabel.getBounds().withX(ratioLabel.getRight()));
    delayTypeLabel.setBounds(wetLevelLabel.getBounds().withX(wetLevelLabel.getRight())
                                                      .withY(wetLevelLabel.getY() + 55));

    dryLevelUnitsLabel.setBounds(0, 153, 103, 30);
    delayTimeUnitsLabel.setBounds(dryLevelUnitsLabel.getBounds().withX(dryLevelUnitsLabel.getRight()));
    feedbackUnitsLabel.setBounds(delayTimeUnitsLabel.getBounds().withX(delayTimeUnitsLabel.getRight()));
    ratioUnitsLabel.setBounds(feedbackUnitsLabel.getBounds().withX(feedbackUnitsLabel.getRight()));
    wetLevelUnitsLabel.setBounds(ratioUnitsLabel.getBounds().withX(ratioUnitsLabel.getRight()));
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

void JDelayAudioProcessorEditor::createDelayTypeComboBox()
{
    delayTypeComboBox.addItem("Normal", 1);
    delayTypeComboBox.addItem("Ping Pong", 2);
    delayTypeComboBox.setSelectedItemIndex(0, juce::dontSendNotification);
    delayTypeComboBox.setJustificationType(juce::Justification::centred);
}