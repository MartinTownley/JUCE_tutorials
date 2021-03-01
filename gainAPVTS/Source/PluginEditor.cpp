/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainAPVTSAudioProcessorEditor::GainAPVTSAudioProcessorEditor (GainAPVTSAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    mGainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 20);
    
    //mGainSlider.addListener (this);
    addAndMakeVisible (mGainSlider);
    
    mGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "GAIN", mGainSlider);
    
    setSize (200, 300);
}

GainAPVTSAudioProcessorEditor::~GainAPVTSAudioProcessorEditor()
{
}

//==============================================================================
void GainAPVTSAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::seagreen);
}

void GainAPVTSAudioProcessorEditor::resized()
{
    mGainSlider.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
}

//void GainAPVTSAudioProcessorEditor::sliderValueChanged (juce::Slider *slider)
//{
//    if (slider == &mGainSlider)
//    {
//        audioProcessor.setGain (mGainSlider.getValue());
//    }
//}
