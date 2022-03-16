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
    // g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
}

void JDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    auto dryLevelSliderArea = bounds.removeFromLeft(95).removeFromTop(160);
    dryLevelSlider.setBounds(dryLevelSliderArea);

    auto delayTimeArea = bounds.removeFromLeft(95).removeFromTop(160);
    delayTimeSlider.setBounds(delayTimeArea);

    auto feedbackArea = bounds.removeFromLeft(95).removeFromTop(160);
    feedbackSlider.setBounds(feedbackArea);

    auto ratioArea = bounds.removeFromLeft(95).removeFromTop(160);
    ratioSlider.setBounds(ratioArea);

    auto wetLevelSliderArea = bounds.removeFromLeft(95).removeFromTop(160);
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

//==============================================================================
void JDelayLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPosProportional,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height);

    g.setColour(juce::Colours::white);
    g.fillEllipse(bounds);

    g.setColour(juce::Colours::black);
    g.drawEllipse(bounds, 1.f);

    if (auto* rswl = dynamic_cast<RotarySliderWithLabels*>(&slider))
    {
        auto center = bounds.getCentre();

        juce::Path rotarySliderPath;

        juce::Rectangle<float> rotarySliderPathRectangle;
        rotarySliderPathRectangle.setLeft(center.getX() - 2);
        rotarySliderPathRectangle.setRight(center.getX() + 2);
        rotarySliderPathRectangle.setTop(bounds.getY());
        rotarySliderPathRectangle.setBottom(center.getY() - rswl->getTextHeight() * 1.5);

        rotarySliderPath.addRoundedRectangle(rotarySliderPathRectangle, 2.f);

        jassert(rotaryStartAngle < rotaryEndAngle);

        auto sliderAngRad = juce::jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);

        rotarySliderPath.applyTransform(juce::AffineTransform().rotated(sliderAngRad, center.getX(), center.getY()));

        g.fillPath(rotarySliderPath);
    }
}

//==============================================================================
void RotarySliderWithLabels::paint(juce::Graphics& g)
{
    auto startAng = juce::degreesToRadians(180.f + 45.f);
    auto endAng = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants<float>::twoPi; // what if 2pi is removed?

    auto range = getRange();

    auto sliderBounds = getSliderBounds();

    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());
    g.setColour(juce::Colours::yellow);
    g.drawRect(sliderBounds);

    getLookAndFeel().drawRotarySlider(g, 
                                      sliderBounds.getX(), 
                                      sliderBounds.getY(), 
                                      sliderBounds.getWidth(), 
                                      sliderBounds.getHeight(), 
                                      juce::jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0), 
                                      startAng, 
                                      endAng, 
                                      *this);
}

juce::Rectangle<int> RotarySliderWithLabels::getSliderBounds() const
{
    // return getLocalBounds();

    auto bounds = getLocalBounds();

    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());

    size -= getTextHeight() * 2;
    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(65);

    return r;
}