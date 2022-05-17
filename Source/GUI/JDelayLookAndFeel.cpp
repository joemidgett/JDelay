// JDelayLookAndFeel.cpp

#include "JDelayLookAndFeel.h"
#include "JDelaySlider.h"

void JDelayLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height);

    g.setColour(juce::Colours::white);
    g.fillEllipse(bounds);

    g.setColour(juce::Colours::black);
    g.drawEllipse(bounds, 1.f);

    if (auto* rswl = dynamic_cast<JDelaySlider*>(&slider))
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

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(comboBoxBounds.toFloat(), 0);

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(comboBoxBounds.toFloat().reduced(0.5f, 0.5f), 0, 1.0f);
}

juce::Font JDelayLookAndFeel::getComboBoxFont(juce::ComboBox& box)
{
    return { juce::jmin(14.0f, (float)box.getHeight() * 0.85f) };
}

void JDelayLookAndFeel::positionComboBoxText(juce::ComboBox& box, juce::Label& label)
{
    label.setBounds(12, 1, box.getWidth() - 30, box.getHeight() - 2);

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