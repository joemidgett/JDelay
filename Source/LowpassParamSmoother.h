// LowpassParamSmoother.h

#pragma once

#include <math.h>
#include <memory>
#include <time.h>

#include <JuceHeader.h>

class LowpassParamSmoother
{
public:

    LowpassParamSmoother() {};
    ~LowpassParamSmoother() {};

    void initializeLowpassSmoothing(float smoothingTimeInMs, float samplingRate)
    {
        const float twoPi = juce::MathConstants<float>::twoPi;

        a = exp(-twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        outputValue = 0.0f;
    }

    inline float processLowpassSmoothing(float inputValue)
    {
        outputValue = (inputValue * b) + (outputValue * a);
        return outputValue;
    }

private:
    float a;
    float b;
    float outputValue;
};