// LowpassParamSmoother.h

#pragma once

#include <JuceHeader.h>

class LowpassParamSmoother
{
public:
    void initializeLowpassSmoothing(float smoothingTimeInMs, float samplingRate);
    float processLowpassSmoothing(float inputValue);

private:
    float a;
    float b;
    float outputValue;
};