/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
JDelayAudioProcessor::JDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor(BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

JDelayAudioProcessor::~JDelayAudioProcessor()
{

}

//==============================================================================
const juce::String JDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JDelayAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String JDelayAudioProcessor::getProgramName(int index)
{
    return {};
}

void JDelayAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void JDelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    stereoDelay.reset(sampleRate);
    
    stereoDelay.createDelayBuffers(sampleRate, 2000.0);

    delayTimeLowpassParamSmoothing.initializeLowpassSmoothing(1500.0, sampleRate);
    ratioLowpassParamSmoothing.initializeLowpassSmoothing(200.0, sampleRate);
    dryLowpassParamSmoothing.initializeLowpassSmoothing(5.0, sampleRate);
    wetLowpassParamSmoothing.initializeLowpassSmoothing(5.0, sampleRate);

    updateParameters();
}

juce::AudioProcessorValueTreeState::ParameterLayout JDelayAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("DRYLEVEL",
                                                           "Dry Level",
                                                            juce::NormalisableRange<float>(-60.0, 12.0, 0.01, 1.0),
                                                            -3.0));

    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAYTIME", 
                                                           "Delay Time", 
                                                            juce::NormalisableRange<float>(0.0, 2000.0, 0.01, 1.0),
                                                            250.0));

    layout.add(std::make_unique<juce::AudioParameterFloat>("FEEDBACK",
                                                           "Feedback",
                                                            juce::NormalisableRange<float>(0.0, 100.0, 0.01, 1.0),
                                                            50.0));

    layout.add(std::make_unique<juce::AudioParameterFloat>("RATIO",
                                                           "Ratio",
                                                           juce::NormalisableRange<float>(0.0, 100.0, 0.01, 1.0),
                                                           50.0));

    layout.add(std::make_unique<juce::AudioParameterFloat>("WETLEVEL",
                                                           "Wet Level",
                                                            juce::NormalisableRange<float>(-60.0, 12.0, 0.01, 1.0),
                                                            -3.0));

    layout.add(std::make_unique<juce::AudioParameterChoice>("DELAYTYPE", 
                                                            "Delay Type", 
                                                             juce::StringArray("Normal", "PingPong"),
                                                             0));

    return layout;
}

void JDelayAudioProcessor::updateParameters()
{
    AudioDelayParameters audioDelayParams = stereoDelay.getParameters();

    audioDelayParams.updateType = delayUpdateType::kLeftPlusRatio;

    audioDelayParams.dryLevel_dB = *apvts.getRawParameterValue("DRYLEVEL");
    audioDelayParams.dryLevel_dB = dryLowpassParamSmoothing.processLowpassSmoothing(audioDelayParams.dryLevel_dB);

    audioDelayParams.leftDelay_mSec = *apvts.getRawParameterValue("DELAYTIME");
    audioDelayParams.leftDelay_mSec = delayTimeLowpassParamSmoothing.processLowpassSmoothing(audioDelayParams.leftDelay_mSec);

    audioDelayParams.feedback_Pct = *apvts.getRawParameterValue("FEEDBACK");

    audioDelayParams.delayRatio_Pct = *apvts.getRawParameterValue("RATIO");
    audioDelayParams.delayRatio_Pct = ratioLowpassParamSmoothing.processLowpassSmoothing(audioDelayParams.delayRatio_Pct);

    audioDelayParams.wetLevel_dB = *apvts.getRawParameterValue("WETLEVEL");
    audioDelayParams.wetLevel_dB = wetLowpassParamSmoothing.processLowpassSmoothing(audioDelayParams.wetLevel_dB);

    audioDelayParams.algorithm = convertIntToEnum((int)*apvts.getRawParameterValue("DELAYTYPE"), delayAlgorithm);

    stereoDelay.setParameters(audioDelayParams);
}

void JDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JDelayAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JDelayAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* leftChannelData = buffer.getWritePointer(0);
    auto* rightChannelData = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        updateParameters();

        float inputFrame[2]{ leftChannelData[i], rightChannelData[i] };
        float outputFrame[2];

        stereoDelay.processAudioFrame(inputFrame, outputFrame, totalNumInputChannels, totalNumOutputChannels);

        buffer.setSample(0, i, outputFrame[0]);
        buffer.setSample(1, i, outputFrame[1]);
    }
}

//==============================================================================
bool JDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JDelayAudioProcessor::createEditor()
{
    return new JDelayAudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void JDelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JDelayAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JDelayAudioProcessor();
}