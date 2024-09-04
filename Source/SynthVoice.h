#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound* sound) override;

    float setPitchBend();

    double noteHz(int midiNoteNumber, double centsOffset);

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void getOsc1Type(float* selection);

    void getOsc2Type(float* selection);
    
    double square(double frequency);

    double saw(double frequency);

    double sinewave(double frequency);

    double triangle(double frequency);

    double setOscType();
     
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release, double sampleRate);
        
    void getWillsParams(float* mGain, float* blend1, float* blend2, float* pitchwheel, float* tunablesemitone);
    
    void stopNote(float velocity, bool allowTailOff) override;
        
    void pitchWheelMoved (int newPitchWheelValue) override{}
    
    void controllerMoved (int controllerNumber, int newControllerValue) override{}
        
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

//=======================================================

private:
    float inputPhase = 0.0;
    double frequency1;
    double frequency2;
    int theWave1, theWave2;

    float masterGain;

    float osc1blend;
    float osc2blend;

    int noteNumber;
    float pitchWheel = 0.0f;
    float pitchBend;
    int tunableSemitone = 1;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
};
