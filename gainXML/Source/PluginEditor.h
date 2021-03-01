/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainXMLAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GainXMLAudioProcessorEditor (GainXMLAudioProcessor&);
    ~GainXMLAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mGainSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainSliderAttachment;
    
    // ================================================
    GainXMLAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainXMLAudioProcessorEditor)
};
