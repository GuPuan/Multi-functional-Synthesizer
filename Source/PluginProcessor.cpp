#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MFSynthesizer::MFSynthesizer()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
    , tree(*this, nullptr, "PARAMETERS",
        {   
            std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.01f, 3.0f, 0.01f), 0.01f),
            std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.01f, 3.0f, 0.01f), 0.01f),
            std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.8f),
            std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.01f, 3.0f, 0.01f), 0.01f),
            std::make_unique<AudioParameterFloat>("wavetype1", "WaveType1", NormalisableRange<float>(0.0f, 3.0f, 1.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("wavetype2", "WaveType2", NormalisableRange<float>(0.0f, 3.0f, 1.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("filterType", "FilterType", NormalisableRange<float>(0.0f, 2.0f, 1.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(20.0f, 20000.0f, 0.1f), 20000.0f),
            std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(0.01f, 5.0f, 0.01f), 1.0f),
            std::make_unique<AudioParameterFloat>("blend1", "Osc1Blend", NormalisableRange<float>(0.0f, 0.5f, 0.01f), 0.25f),
            std::make_unique<AudioParameterFloat>("blend2", "Osc2Blend", NormalisableRange<float>(0.0f, 0.5f, 0.01f), 0.0f),
            std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 2.0f, 0.1f), 1.0f),
            std::make_unique<AudioParameterFloat>("pitchwheel", "PitchWheel", NormalisableRange<float>(-1000.0f, 1000.0f, 0.1f), 0.0f),
            std::make_unique<AudioParameterFloat>("tunablesemitone", "TunableSemitone", NormalisableRange<float>(1, 12, 1), 1),
            std::make_unique<AudioParameterFloat>("size", "Size", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
            std::make_unique<AudioParameterFloat>("damping", "Damping", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
            std::make_unique<AudioParameterFloat>("stereoWidth", "StereoWidth", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
            std::make_unique<AudioParameterFloat>("dry", "Dry", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f),
            std::make_unique<AudioParameterFloat>("wet", "Wet", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
            std::make_unique<AudioParameterFloat>("freeze", "Freeze", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
        })
#endif
{
    mySynth.clearVoices();
    
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

MFSynthesizer::~MFSynthesizer()
{
}

//==============================================================================
const String MFSynthesizer::getName() const
{
    return JucePlugin_Name;
}

bool MFSynthesizer::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MFSynthesizer::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MFSynthesizer::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MFSynthesizer::getTailLengthSeconds() const
{
    return 0.0;
}

int MFSynthesizer::getNumPrograms()
{
    return 1;   
}

int MFSynthesizer::getCurrentProgram()
{
    return 0;
}

void MFSynthesizer::setCurrentProgram (int index)
{
}

const String MFSynthesizer::getProgramName (int index)
{
    return {};
}

void MFSynthesizer::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MFSynthesizer::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    filter.reset();
    filter.prepare(spec);
    updateFilterParams();
}

void MFSynthesizer::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MFSynthesizer::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif

void MFSynthesizer::updateFilterParams()
{
    
    float filterChoice = *tree.getRawParameterValue("filterType");
    float filterFrequency = *tree.getRawParameterValue("filterCutoff");
    float filterQ = *tree.getRawParameterValue("filterRes");
    
    if (filterChoice == 0)
    {
        filterParams.type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        filterParams.setCutOffFrequency(lastSampleRate,filterFrequency, filterQ);
    }
    
    if (filterChoice == 1)
    {
        filterParams.type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        filterParams.setCutOffFrequency(lastSampleRate, filterFrequency, filterQ);
    }
    
    if (filterChoice == 2)
    {
        filterParams.type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        filterParams.setCutOffFrequency(lastSampleRate, filterFrequency, filterQ);
    }
    filter.parameters = filterParams;
}

void MFSynthesizer::updateReverbParams() {
    reverbParams.roomSize = *tree.getRawParameterValue("size");
    reverbParams.width = *tree.getRawParameterValue("damping");
    reverbParams.width = *tree.getRawParameterValue("stereoWidth");
    reverbParams.dryLevel = *tree.getRawParameterValue("dry");
    reverbParams.wetLevel = *tree.getRawParameterValue("wet");
    reverbParams.freezeMode = *tree.getRawParameterValue("freeze");
    reverb.setParameters(reverbParams);
}

void MFSynthesizer::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals; 
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getEnvelopeParams((float*)tree.getRawParameterValue("attack"),
                                       (float*)tree.getRawParameterValue("decay"),
                                       (float*)tree.getRawParameterValue("sustain"),
                                       (float*)tree.getRawParameterValue("release"),
                                                                getSampleRate());
            
            myVoice->getOsc1Type((float*)tree.getRawParameterValue("wavetype1"));
            myVoice->getOsc2Type((float*)tree.getRawParameterValue("wavetype2"));
                        
            myVoice->getWillsParams((float*)tree.getRawParameterValue("mastergain"),
                                    (float*)tree.getRawParameterValue("blend1"),
                                    (float*)tree.getRawParameterValue("blend2"),
                                    (float*)tree.getRawParameterValue("pitchwheel"),
                                    (float*)tree.getRawParameterValue("tunablesemitone"));
        }
    }
   
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    dsp::AudioBlock<float> block (buffer);

    updateFilterParams();
    filter.process(dsp::ProcessContextReplacing<float> (block));

    updateReverbParams();
    reverb.process(juce::dsp::ProcessContextReplacing<float> (block));
}

//==============================================================================
bool MFSynthesizer::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MFSynthesizer::createEditor()
{
    return new MFSynthesizerEditor (*this);
}

//==============================================================================
void MFSynthesizer::getStateInformation (MemoryBlock& destData)
{
    
}

void MFSynthesizer::setStateInformation (const void* data, int sizeInBytes)
{
    
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MFSynthesizer();
}
