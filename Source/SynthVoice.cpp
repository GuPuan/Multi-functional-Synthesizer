#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"

bool SynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast <SynthSound*>(sound) != nullptr;
}

float SynthVoice::setPitchBend()
{
    if (pitchWheel > 0)
    {
        pitchBend = ((pitchWheel - 0) / 1000) * tunableSemitone * 100;
    }
    else
    {
        pitchBend = ((0 - pitchWheel) / -1000) * tunableSemitone * 100;
    }
    return pitchBend;
}

double SynthVoice::noteHz(int midiNoteNumber, double centsOffset)
{
    double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= std::pow(2.0, centsOffset / 1200);
    return hertz;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    noteNumber = midiNoteNumber;
    adsr.noteOn();
    frequency1 = noteHz(noteNumber, 0);
    frequency2 = noteHz(noteNumber, setPitchBend());
}

void SynthVoice::getOsc1Type(float* selection)
{
    theWave1 = *selection;
}

void SynthVoice::getOsc2Type(float* selection)
{
    theWave2 = *selection;
}

double SynthVoice::square(double frequency) {
    double in = 0.0;
    inputPhase += frequency / getSampleRate();
    while (inputPhase >= 1.0) inputPhase -= 1.0;
    in = (inputPhase < 0.5 ? 1.0f : -1.0f);
    return in;
}

double SynthVoice::saw(double frequency) {
    double in = 0.0;
    inputPhase += frequency / getSampleRate();
    while (inputPhase >= 1.0) inputPhase -= 1.0;
    in = 2.0f * inputPhase - 1.0f;
    return in;
}

double SynthVoice::sinewave(double frequency) {
    double in = 0.0;
    inputPhase += frequency / getSampleRate();
    while (inputPhase >= 1.0) inputPhase -= 1.0;
    in = sinf(juce::MathConstants<float>::twoPi * inputPhase);
    return in;
}

double SynthVoice::triangle(double frequency) {
    double in = 0.0;
    inputPhase += frequency / getSampleRate();
    while (inputPhase >= 1.0) inputPhase -= 1.0;
    if (inputPhase < 0.5)
        in = 4.0f * inputPhase - 1.0f;
    else
        in = (-4.0f) * inputPhase + 3.0f;
    return in;
}

double SynthVoice::setOscType()
{
    double sample1, sample2;
    switch (theWave1)
    {
    case 0:
        sample1 = square(frequency1);
        break;
    case 1:
        sample1 = saw(frequency1);
        break;
    case 2:
        sample1 = sinewave(frequency1);
        break;
    case 3:
        sample1 = triangle(frequency1);
    }

    switch (theWave2)
    {
    case 0:
        sample2 = square(frequency2);
        break;
    case 1:
        sample2 = saw(frequency2);
        break;
    case 2:
        sample2 = sinewave(frequency2);
        break;
    case 3:
        sample2 = triangle(frequency2);
    }
    return osc1blend * sample1 + osc2blend * sample2;
}

void SynthVoice::getEnvelopeParams(float* attack, float* decay, float* sustain, float* release, double sampleRate)
{
    adsr.setSampleRate(sampleRate);
    adsrParams.attack = *attack;
    adsrParams.decay = *decay;
    adsrParams.sustain = *sustain;
    adsrParams.release = *release;
    adsr.setParameters(adsrParams);
}

void SynthVoice::getWillsParams(float* mGain, float* blend1, float* blend2, float* pitchwheel, float* tunablesemitone)
{
    masterGain = *mGain;
    osc1blend = *blend1;
    osc2blend = *blend2;
    pitchWheel = *pitchwheel;
    tunableSemitone = *tunablesemitone;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    allowTailOff = true;
    adsr.noteOff();
    if (velocity == 0)
    clearCurrentNote();
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; ++sample) {
        float adsrValue = adsr.getNextSample();
        float nextSample = setOscType() * adsrValue * masterGain;
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
            outputBuffer.addSample(channel, startSample, nextSample);
        }
        ++startSample;
    }
}