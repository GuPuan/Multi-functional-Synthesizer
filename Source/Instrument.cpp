#include "../JuceLibraryCode/JuceHeader.h"
#include "Instrument.h"

Instrument::Instrument(MFSynthesizer& p) :
    processor(p)
{
    setSize(200, 230);

    instruMenu.addItem("Guitar", 1);
    instruMenu.addItem("Violin", 2);
    instruMenu.addItem("Piano", 3);
    instruMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&instruMenu);
    instruSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "instrutype", instruMenu);
}

Instrument::~Instrument()
{
}

void Instrument::paint(Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 50, getWidth(), 30);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    Font font(17.0f);
    g.setFont(font);
    g.drawText("Intsrument Menu", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area(25, 25, 150, 200);
    g.setColour(Colours::orange);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Instrument::resized()
{
    const int boundaryReduction = 40;
    const int menuHeight = 25; 
    const int menuVerticalOffset = 40; 

    juce::Rectangle<int> area = getLocalBounds().reduced(boundaryReduction);

    area.removeFromTop(menuVerticalOffset);
    instruMenu.setBounds(area.removeFromTop(menuHeight));
}