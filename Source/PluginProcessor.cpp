/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
                       ), apvts(*this, nullptr, "Parameters", createParameters())
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

    updateParameters();
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

    /*auto dt = apvts.getRawParameterValue("DELAY TIME");
    dt->load();*/

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    switch ((int)*apvts.getRawParameterValue("DELAYTYPE"))
    //    {
    //        case 0:
    //            DBG("Normal");
    //            break;
    //        case 1:
    //            DBG("PingPong");
    //            break;
    //    }
    //}
}

//==============================================================================
bool JDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JDelayAudioProcessor::createEditor()
{
    return new JDelayAudioProcessorEditor (*this);
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

juce::AudioProcessorValueTreeState::ParameterLayout JDelayAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAY TIME", "Delay Time", 0.0, 2000.0, 250.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", 0.0, 100.0, 50.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio", 0.0, 100.0, 50.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WETLEVEL", "Wet Level", -60.0, 12.0, -3.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRYLEVEL", "Dry Level", -60.0, 12.0, -3.0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("DELAYTYPE", "Delay Type", juce::StringArray("Normal", "PingPong"), 0));

    return { params.begin(), params.end() };
}

void JDelayAudioProcessor::updateParameters()
{
    AudioDelayParameters audioDelayParams = stereoDelay.getParameters();
    audioDelayParams.leftDelay_mSec = *apvts.getRawParameterValue("DELAY TIME");
    audioDelayParams.feedback_Pct = *apvts.getRawParameterValue("FEEDBACK");
    audioDelayParams.delayRatio_Pct = *apvts.getRawParameterValue("RATIO");
    audioDelayParams.updateType = delayUpdateType::kLeftPlusRatio;

    audioDelayParams.dryLevel_dB = *apvts.getRawParameterValue("DRYLEVEL");
    audioDelayParams.wetLevel_dB = *apvts.getRawParameterValue("WETLEVEL");

    // audioDelayParams.algorithm = convertIntToEnum(delayType, delayAlgorithm);

    stereoDelay.setParameters(audioDelayParams);
}