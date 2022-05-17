// JDelayComboBox.cpp

#include "JDelayComboBox.h"

JDelayComboBox::JDelayComboBox() : juce::ComboBox()
{
	setLookAndFeel(&lnf);
}

JDelayComboBox::~JDelayComboBox()
{
	setLookAndFeel(nullptr);
}