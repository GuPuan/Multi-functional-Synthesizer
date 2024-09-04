
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "Mastergui.h"
#include "Instrument.h"
#include "InstrumentListener.h"
#include "Reverb.h"

//==============================================================================
/**
*/
class MFSynthesizerEditor  : public AudioProcessorEditor

{
public:
    MFSynthesizerEditor (MFSynthesizer&);
    ~MFSynthesizerEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MFSynthesizer& processor;
    
    Oscillator oscGui;
    Envelope envGui;
    Filter filterGui;
    Mastergui masterGui;
    Instrument instruGui;
    ReverbUI reverbGui;

    std::unique_ptr<InstrumentListener> listener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MFSynthesizerEditor)
};
