#include "../JuceLibraryCode/JuceHeader.h"
#include "Reverb.h"

ReverbUI::ReverbUI(MFSynthesizer& p) :
    processor(p)
{
    setSize(1000, 200);

    size.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    size.setRange(0.0, 1.0);
    size.setValue(0.0);
    size.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&size);
    sizeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "size", size);
    sizeLabel.setText("Size", dontSendNotification);
    sizeLabel.setJustificationType(Justification::centred);
    sizeLabel.attachToComponent(&size, false);
    addAndMakeVisible(&sizeLabel);

    damping.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    damping.setRange(0.0, 1.0);
    damping.setValue(0.0);
    damping.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&damping);
    dampingVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "damping", damping);
    dampingLabel.setText("Damping", dontSendNotification);
    dampingLabel.setJustificationType(Justification::centred);
    dampingLabel.attachToComponent(&damping, false);
    addAndMakeVisible(&dampingLabel);

    stereoWidth.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    stereoWidth.setRange(0.0, 1.0);
    stereoWidth.setValue(0.0);
    stereoWidth.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&stereoWidth);
    stereoWidthVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "stereoWidth", stereoWidth);
    stereoWidthLabel.setText("StereoWidth", dontSendNotification);
    stereoWidthLabel.setJustificationType(Justification::centred);
    stereoWidthLabel.attachToComponent(&stereoWidth, false);
    addAndMakeVisible(&stereoWidthLabel);

    dry.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dry.setRange(0.0, 1.0);
    dry.setValue(1.0);
    dry.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&dry);
    dryVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dry", dry);
    dryLabel.setText("Dry", dontSendNotification);
    dryLabel.setJustificationType(Justification::centred);
    dryLabel.attachToComponent(&dry, false);
    addAndMakeVisible(&dryLabel);

    wet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wet.setRange(0.0, 1.0);
    wet.setValue(0.0);
    wet.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&wet);
    wetVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "wet", wet);
    wetLabel.setText("Wet", dontSendNotification);
    wetLabel.setJustificationType(Justification::centred);
    wetLabel.attachToComponent(&wet, false);
    addAndMakeVisible(&wetLabel);

    freeze.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freeze.setRange(0.0, 1.0);
    freeze.setValue(0.0);
    freeze.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&freeze);
    freezeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "freeze", freeze);
    freezeLabel.setText("Freeze", dontSendNotification);
    freezeLabel.setJustificationType(Justification::centred);
    freezeLabel.attachToComponent(&freeze, false);
    addAndMakeVisible(&freezeLabel);
}

ReverbUI::~ReverbUI()
{
}

void ReverbUI::paint(Graphics& g)
{
    juce::Rectangle <float> area(15, 15, 835, 140);
    g.setColour(Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void ReverbUI::resized()
{
    auto area = getLocalBounds().reduced(15);
    auto totalWidth = area.getWidth();
    int knobWidth = totalWidth / 6; 

    int knobHeight = 100; 
    int startY = (area.getHeight() - knobHeight) / 2; 

    size.setBounds(area.getX(), startY, knobWidth, knobHeight);
    damping.setBounds(area.getX() + knobWidth * 0.85, startY, knobWidth, knobHeight);
    stereoWidth.setBounds(area.getX() + knobWidth * 1.7, startY, knobWidth, knobHeight);
    dry.setBounds(area.getX() + knobWidth * 2.55, startY, knobWidth, knobHeight);
    wet.setBounds(area.getX() + knobWidth * 3.5, startY, knobWidth, knobHeight);
    freeze.setBounds(area.getX() + knobWidth * 4.35, startY, knobWidth, knobHeight);
}