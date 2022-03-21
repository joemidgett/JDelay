// JDelayWetLevelLookAndFeel.h

#include <JuceHeader.h>

#include "JDelayLookAndFeel.h"

#pragma once

class JDelayWetLevelLookAndFeel : public JDelayLookAndFeel
{
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider& slider) override;
private:

};