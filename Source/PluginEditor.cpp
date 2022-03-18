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
    dryLevelSlider.labels.add({ 0.f, "Dry Level" });
    delayTimeSlider.labels.add({ 0.f, "Delay Time" });
    feedbackSlider.labels.add({ 0.f, "Feedback" });
    ratioSlider.labels.add({ 0.f, "L/R Ratio" });
    wetLevelSlider.labels.add({ 0.f, "Wet Level" });

    addAndMakeVisible(dryLevelUnitsLabel);
    dryLevelUnitsLabel.setFont(juce::Font(14.0f));
    dryLevelUnitsLabel.setText("dB", juce::dontSendNotification);
    dryLevelUnitsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    dryLevelUnitsLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(delayTimeUnitsLabel);
    delayTimeUnitsLabel.setFont(juce::Font(14.0f));
    delayTimeUnitsLabel.setText("mSec", juce::dontSendNotification);
    delayTimeUnitsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    delayTimeUnitsLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(feedbackUnitsLabel);
    feedbackUnitsLabel.setFont(juce::Font(14.0f));
    feedbackUnitsLabel.setText("%", juce::dontSendNotification);
    feedbackUnitsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    feedbackUnitsLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(ratioUnitsLabel);
    ratioUnitsLabel.setFont(juce::Font(14.0f));
    ratioUnitsLabel.setText("%", juce::dontSendNotification);
    ratioUnitsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ratioUnitsLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(wetLevelUnitsLabel);
    wetLevelUnitsLabel.setFont(juce::Font(14.0f));
    wetLevelUnitsLabel.setText("dB", juce::dontSendNotification);
    wetLevelUnitsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    wetLevelUnitsLabel.setJustificationType(juce::Justification::centred);

    for (auto* comp : getJDelayComponents())
    {
        addAndMakeVisible(comp);
    }

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 180);
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

    auto delayTypeComboBoxArea = bounds.removeFromLeft(115).removeFromBottom(125).removeFromTop(45);
    delayTypeComboBox.addItem("Normal", 1);
    delayTypeComboBox.addItem("Ping Pong", 2);
    delayTypeComboBox.setJustificationType(juce::Justification::centred);
    delayTypeComboBox.setBounds(delayTypeComboBoxArea);

    dryLevelUnitsLabel.setBounds(-242, 145, getWidth() - 20, 30);
    delayTimeUnitsLabel.setBounds(-147, 145, getWidth() - 20, 30);
    feedbackUnitsLabel.setBounds(-52, 145, getWidth() - 20, 30);
    ratioUnitsLabel.setBounds(42, 145, getWidth() - 20, 30);
    wetLevelUnitsLabel.setBounds(138, 145, getWidth() - 20, 30);
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

void JDelayLookAndFeel::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
                                     int buttonX, int buttonY, int buttonW, int buttonH,
                                     juce::ComboBox& box)
{
    auto comboBoxBounds = juce::Rectangle<int>(0, 0, width, height);

    // g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(comboBoxBounds.toFloat(), 0);

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(comboBoxBounds.toFloat().reduced(0.5f, 0.5f), 0, 1.0f);

    /*Rectangle<int> arrowZone(width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
    path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
    path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);*/

    /*g.setColour(box.findColour(ComboBox::arrowColourId).withAlpha((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath(path, PathStrokeType(2.0f));*/
    
}

juce::Font JDelayLookAndFeel::getComboBoxFont(juce::ComboBox& box)
{
    return { juce::jmin(14.0f, (float)box.getHeight() * 0.85f) };
}

void JDelayLookAndFeel::positionComboBoxText(juce::ComboBox& box, juce::Label& label)
{
    label.setBounds(12, 1,
        box.getWidth() - 30,
        box.getHeight() - 2);

    label.setFont(getComboBoxFont(box));
}

void JDelayLookAndFeel::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
    const bool isSeparator, const bool isActive,
    const bool isHighlighted, const bool isTicked,
    const bool hasSubMenu, const juce::String& text,
    const juce::String& shortcutKeyText,
    const juce::Drawable* icon, const juce::Colour* const textColourToUse)
{
    auto textColour = (textColourToUse == nullptr ? findColour(juce::PopupMenu::textColourId)
        : *textColourToUse);

    auto r = area.reduced(3);

    if (isHighlighted && isActive)
    {
        // g.setColour(findColour(juce::PopupMenu::highlightedBackgroundColourId));
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(r);

        g.setColour(findColour(juce::PopupMenu::highlightedTextColourId));
    }
    else
    {
        g.setColour(textColour.withMultipliedAlpha(isActive ? 1.0f : 0.5f));
    }

    r.reduce(juce::jmin(5, area.getWidth() / 20), 0);

    auto font = getPopupMenuFont();

    auto maxFontHeight = 14.f;
    font.setHeight(maxFontHeight);
    g.setFont(font);

    r.removeFromRight(3);
    g.drawFittedText(text, r, juce::Justification::centredLeft, 1);

    if (shortcutKeyText.isNotEmpty())
    {
        auto f2 = font;
        f2.setHeight(f2.getHeight() * 0.75f);
        f2.setHorizontalScale(0.95f);
        g.setFont(f2);

        g.drawText(shortcutKeyText, r, juce::Justification::centredRight, true);
    }
}

void JDelayLookAndFeel::getIdealPopupMenuItemSize(const juce::String& text, const bool isSeparator,
    int standardMenuItemHeight, int& idealWidth, int& idealHeight)
{
    auto font = getPopupMenuFont();

    if (standardMenuItemHeight > 0 && font.getHeight() > (float)standardMenuItemHeight / 1.3f)
        font.setHeight((float)standardMenuItemHeight / 1.3f);

    idealHeight = 20.f;
    idealWidth = 20.f;
}

//==============================================================================
void RotarySliderWithLabels::paint(juce::Graphics& g)
{
    auto startAng = juce::degreesToRadians(180.f + 45.f);
    auto endAng = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants<float>::twoPi; // what if 2pi is removed?

    auto range = getRange();

    auto sliderBounds = getSliderBounds();

    //g.setColour(juce::Colours::red);
    //g.drawRect(getLocalBounds());
    //g.setColour(juce::Colours::yellow);
    //g.drawRect(sliderBounds);

    getLookAndFeel().drawRotarySlider(g, 
                                      sliderBounds.getX(), 
                                      sliderBounds.getY(), 
                                      sliderBounds.getWidth(), 
                                      sliderBounds.getHeight(), 
                                      juce::jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0), 
                                      startAng, 
                                      endAng, 
                                      *this);

    g.setColour(juce::Colours::white);
    g.setFont(getTextHeight());

    auto numChoices = labels.size();
    for (int labelChoice = 0; labelChoice < numChoices; ++labelChoice)
    {
        auto rotarySliderLabelPos = labels[labelChoice].rotarySliderLabelPos;
        
        juce::Rectangle<float> r;
        auto rotarySliderLabelText = labels[labelChoice].rotarySliderLabelText;
        r.setSize(g.getCurrentFont().getStringWidth(rotarySliderLabelText), getTextHeight());

        r.setCentre(sliderBounds.getCentreX(), sliderBounds.getCentreY() - 55);

        g.drawFittedText(rotarySliderLabelText, r.toNearestInt(), juce::Justification::centred, 1);
    }
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
    r.setY(40);

    return r;
}