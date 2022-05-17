// JDelayComboBox.h

#include <JuceHeader.h>

#include "JDelayLookAndFeel.h"

#pragma once

class JDelayComboBox : public juce::ComboBox
{
public:
    JDelayComboBox();

    ~JDelayComboBox()
    {
        setLookAndFeel(nullptr);
    }

private:
    JDelayLookAndFeel lnf;
};