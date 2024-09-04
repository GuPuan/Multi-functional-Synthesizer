#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

Filter::Filter(MFSynthesizer& p) :
processor(p)
{
    setSize(200, 200);
    
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterType", filterMenu);
    
    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 20000.0);
    filterCutoff.setValue (20000.0);
    filterCutoff.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&filterCutoff);
    filterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(0.1,5.0);
    filterRes.setValue(1.0);
    filterRes.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&filterRes);
    resVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterRes", filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    
    juce::Rectangle<int> titleArea1(36, 65, 45, 20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    Font font(15.0f);
    g.setFont(font);
    g.drawText("Cut-Off", titleArea1, Justification::centred);

    juce::Rectangle<int> titleArea2(97, 68, 70, 15);
    g.drawText("Resonance", titleArea2, Justification::centred);
    

    juce::Rectangle <float> area (15, 15, 165, 165);   
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{    
    filterMenu.setBounds(40,25,120,20);
    filterCutoff.setBounds (20, 90, 80, 80);
    filterRes.setBounds (100, 90, 80, 80);
}
