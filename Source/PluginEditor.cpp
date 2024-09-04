#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MFSynthesizerEditor::MFSynthesizerEditor (MFSynthesizer& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p),  envGui(p), filterGui(p), masterGui(p), instruGui(p), reverbGui(p)
{
    setSize (900, 650);
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&filterGui);
    addAndMakeVisible(&masterGui);
    addAndMakeVisible(&instruGui);
    addAndMakeVisible(&reverbGui);
    listener = std::make_unique<InstrumentListener>(instruGui, processor);
}

MFSynthesizerEditor::~MFSynthesizerEditor()
{
}

//==============================================================================
void MFSynthesizerEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void MFSynthesizerEditor::resized()
{
    instruGui.setBounds(10, 10, 200, 250);

    masterGui.setBounds(instruGui.getRight()+10, 10, 420, 230);

    oscGui.setBounds(instruGui.getX(), masterGui.getBottom()+10, 420, 200);

    filterGui.setBounds(oscGui.getRight()+5, oscGui.getY(), masterGui.getRight() - oscGui.getRight()-20, 200);

    envGui.setBounds(masterGui.getRight()+10, masterGui.getY() + 14, 300, 450);

    reverbGui.setBounds(oscGui.getX(), oscGui.getY()+oscGui.getHeight(), 1000, 220);
}


