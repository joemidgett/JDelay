// JDelayComboBox.h

#include <JuceHeader.h>

#include "JDelayLookAndFeel.h"

#pragma once

class JDelayComboBox : public juce::ComboBox
{
public:
    JDelayComboBox() : juce::ComboBox()
    {
        setLookAndFeel(&lnf);
    }

    ~JDelayComboBox()
    {
        setLookAndFeel(nullptr);
    }


private:
    JDelayLookAndFeel lnf;
};