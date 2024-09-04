
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class Mastergui    : public Component
{
public:
    Mastergui(MFSynthesizer&);
    ~Mastergui();
    
    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    Slider mastergainSlider;
    Slider pitchwheelSlider;
    Slider tunableSemitoneSlider;
      
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pitchwheelVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tunableSemitoneVal;
    
    MFSynthesizer& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mastergui)
};
