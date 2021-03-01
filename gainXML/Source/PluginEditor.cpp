/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainXMLAudioProcessorEditor::GainXMLAudioProcessorEditor (GainXMLAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    mGainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 20);
    
   
    addAndMakeVisible (mGainSlider);
    
    mGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "GAIN", mGainSlider);
    
    setSize (200, 300);
}

GainXMLAudioProcessorEditor::~GainXMLAudioProcessorEditor()
{
}

//==============================================================================
void GainXMLAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::mediumpurple);
}

void GainXMLAudioProcessorEditor::resized()
{
     mGainSlider.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
}
