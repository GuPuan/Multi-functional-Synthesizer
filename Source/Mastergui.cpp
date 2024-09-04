//======================================================
#include "../JuceLibraryCode/JuceHeader.h"
#include "Mastergui.h"

//==============================================================================
Mastergui::Mastergui(MFSynthesizer& p) :
processor(p)
{
    setSize(200, 400);
    
    //slider initialization values
    mastergainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mastergainSlider.setRange(0.0f, 2.0f);
    mastergainSlider.setValue(1.0f);
    mastergainSlider.setTextBoxStyle(Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(&mastergainSlider);
    
    pitchwheelSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pitchwheelSlider.setRange(-1000, 1000, 1);
    pitchwheelSlider.setValue(0);
    pitchwheelSlider.setTextBoxStyle(Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(&pitchwheelSlider);

    tunableSemitoneSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tunableSemitoneSlider.setRange(1, 12, 1);
    tunableSemitoneSlider.setValue(1);
    tunableSemitoneSlider.setTextBoxStyle(Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(&tunableSemitoneSlider);
    
    //sends value of the sliders to the tree state in the processor
    mastergainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "mastergain", mastergainSlider);
    pitchwheelVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "pitchwheel", pitchwheelSlider);
    tunableSemitoneVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "tunablesemitone", tunableSemitoneSlider);

}

Mastergui::~Mastergui()
{
}

void Mastergui::paint (Graphics& g)
{
    // Paints the background and sets up a title area at the top
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::black); // Sets background color
    g.setColour(Colours::white); // Sets text color
    Font font(17.0f);
    g.setFont(font);
    g.drawText("Master Volume", 65, 40, 260, 20, Justification::centred);
    g.drawText("Pitch Wheel For Wave2", 50, 90, 260, 20, Justification::centred);
    g.drawText("Tunable Semitone For Wave2", 50, 150, 260, 20, Justification::centred);

    juce::Rectangle <float> area(10, 25, 390, 200);

    g.setColour(Colours::red);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Mastergui::resized()
{
    mastergainSlider.setBounds(40, 20, 350, 100);
    pitchwheelSlider.setBounds(40, 75, 350,100 );
    tunableSemitoneSlider.setBounds(40, 135,350,100);
}




