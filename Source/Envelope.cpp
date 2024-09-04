#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(MFSynthesizer& p) :
processor(p)
{
    setSize(250, 500);
        attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        attackSlider.setRange(0.01f, 3.0f);
        attackSlider.setValue(0.01f);
        attackSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 35, 25);
        addAndMakeVisible(&attackSlider);
    
        decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        decaySlider.setRange(0.01f, 3.0f);
        decaySlider.setValue(0.01f);
        decaySlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 35, 25);
        addAndMakeVisible(&decaySlider);
    
        sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        sustainSlider.setRange(0.0f, 1.0f);
        sustainSlider.setValue(0.8f);
        sustainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 35, 25);
        addAndMakeVisible(&sustainSlider);
    
        releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        releaseSlider.setRange(0.01f, 3.0f);
        releaseSlider.setValue(0.01f);
        releaseSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 35, 25);
        addAndMakeVisible(&releaseSlider);
    
        attackVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
        decayVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
        sustainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
        releaseVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    Font font(18.0f);
    g.setFont(font);
    g.drawText ("A", 30, 350, 20, 20, Justification::centredTop);
    g.drawText ("D", 71, 350, 20, 20, Justification::centredTop);
    g.drawText ("S", 112, 350, 20, 20, Justification::centredTop);
    g.drawText ("R", 153, 350, 20, 20, Justification::centredTop);   
    juce::Rectangle <float> area (5, 10, 205, 395);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    int startX = 25; 
    int startY = 35;
    int sliderWidth = 35;
    int sliderHeight = 300;
    int spacing = 6; 
    attackSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    decaySlider.setBounds(startX + sliderWidth + spacing, startY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(startX + 2 * (sliderWidth + spacing), startY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(startX + 3 * (sliderWidth + spacing), startY, sliderWidth, sliderHeight);
}



