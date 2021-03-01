/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainAPVTSAudioProcessor::GainAPVTSAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "Parameters", createParams())
#endif
{
    mAPVTS.state.addListener (this);  //listening for changes in our valueTree
}

GainAPVTSAudioProcessor::~GainAPVTSAudioProcessor()
{
}

//==============================================================================
const juce::String GainAPVTSAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainAPVTSAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainAPVTSAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainAPVTSAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainAPVTSAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainAPVTSAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainAPVTSAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainAPVTSAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainAPVTSAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainAPVTSAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainAPVTSAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

void GainAPVTSAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainAPVTSAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainAPVTSAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = channelData[sample] * juce::Decibels::decibelsToGain (mGain);
        }
    }
    
    if (mShouldUpdate)
    {
        updateGain();
    }
}

//==============================================================================
bool GainAPVTSAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainAPVTSAudioProcessor::createEditor()
{
    return new GainAPVTSAudioProcessorEditor (*this);
}

//==============================================================================
void GainAPVTSAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainAPVTSAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void GainAPVTSAudioProcessor::updateGain ()
{
    mGain = mAPVTS.getRawParameterValue ("GAIN")->load();
}


juce::AudioProcessorValueTreeState::ParameterLayout GainAPVTSAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto gainParam = std::make_unique<juce::AudioParameterFloat> ("GAIN", "Gain", -65.0f, 6.0f, 0.0f);
    
    params.push_back (std::move(gainParam));
                      
    return { params.begin(), params.end()};
}

void GainAPVTSAudioProcessor::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    //this will call any time a value has changed in the value tree. So any time anyone pushes a slider etc, this will get called
    mShouldUpdate = true;
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainAPVTSAudioProcessor();
}
