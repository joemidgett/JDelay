// JDelayRatioLookAndFeel.h

#include <JuceHeader.h>

#include "JDelayLookAndFeel.h"

#pragma once

class JDelayRatioLookAndFeel : public JDelayLookAndFeel
{
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
private:

};