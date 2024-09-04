#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator : public Component
{
public:
    Oscillator(MFSynthesizer&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
    MFSynthesizer& processor;

    ComboBox oscMenu1; 
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection1;

    ComboBox oscMenu2;
    Slider Blendslider1;
    Slider Blendslider2;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
