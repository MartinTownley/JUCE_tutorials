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
class GainAPVTSAudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    GainAPVTSAudioProcessorEditor (GainAPVTSAudioProcessor&);
    ~GainAPVTSAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //==============================================================================
    
    
private:
    juce::Slider mGainSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainSliderAttachment; 
    
    GainAPVTSAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAPVTSAudioProcessorEditor)
};
