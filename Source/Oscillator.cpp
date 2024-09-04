

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(MFSynthesizer& p) :
processor(p)
{
    setSize(400, 200);
    
    oscMenu1.addItem("Square", 1);
    oscMenu1.addItem("Saw", 2);
    oscMenu1.addItem("Sine", 3);
    oscMenu1.addItem("Triangle", 4);
    oscMenu1.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscMenu1);
    waveSelection1 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype1", oscMenu1);

    oscMenu2.addItem("Square", 1);
    oscMenu2.addItem("Saw", 2);
    oscMenu2.addItem("Sine", 3);
    oscMenu2.addItem("Triangle", 4);
    oscMenu2.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscMenu2);
    waveSelection2 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype2", oscMenu2);
    
    Blendslider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider1.setRange(0.0f, 0.5f);
    Blendslider1.setValue(0.25f);
    Blendslider1.setSliderStyle(juce::Slider::LinearHorizontal);
    Blendslider1.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(&Blendslider1);
    blendVal1 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend1", Blendslider1);

    Blendslider2.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider2.setRange(0.0f, 0.5f);
    Blendslider2.setValue(0.0f);
    Blendslider2.setSliderStyle(juce::Slider::LinearHorizontal);
    Blendslider2.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(&Blendslider2);
    blendVal2 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend2", Blendslider2);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    juce::Rectangle<int> titleArea1(33, 35, 45, 20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    Font font(15.0f);
    g.setFont(font);
    g.drawText("Wave1", titleArea1, Justification::centredLeft);
    juce::Rectangle<int> titleArea2(33, 100, 50, 20);
    g.drawText("Wave2", titleArea2, Justification::centredLeft);

    // Drawing outlines
    juce::Rectangle <float> area(15, 15, 380, 170);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area.toFloat(), 20.0f, 2.0f);
}

void Oscillator::resized()
{
    oscMenu1.setBounds(100,35,90,20); 
    oscMenu2.setBounds(100, 100, 90, 20);
    Blendslider1.setBounds(20,60,350,25);
    Blendslider2.setBounds(20, 130, 350, 25);
}
