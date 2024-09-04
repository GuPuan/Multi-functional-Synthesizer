#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"

//==============================================================================
/**
*/
class MFSynthesizer  : public AudioProcessor
{
public:
    //==============================================================================
    MFSynthesizer();
    ~MFSynthesizer();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateReverbParams();
    void updateFilterParams();

    AudioProcessorValueTreeState tree;

private:
    Synthesiser mySynth;
    SynthVoice* myVoice;

    dsp::StateVariableFilter::Filter<float> filter;
    dsp::StateVariableFilter::Parameters<float> filterParams;

    juce::dsp::Reverb reverb;
    juce::Reverb::Parameters reverbParams;

    double lastSampleRate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MFSynthesizer)
};
