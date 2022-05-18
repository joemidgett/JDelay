// JDelaySlider.h

#include <JuceHeader.h>

#include "./JDelayLookAndFeel.h"

#pragma once

class JDelaySlider : public juce::Slider
{
public:
    JDelaySlider(juce::RangedAudioParameter& rap, const juce::String& unitSuffix);

    ~JDelaySlider()
    {
        setLookAndFeel(nullptr);
    }

    struct RotarySliderLabelPosition
    {
        float rotarySliderLabelPos;
        juce::String rotarySliderLabelText;
    };

    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 14; }

};