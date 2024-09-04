#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class ReverbUI : public Component
{
public:
    ReverbUI(MFSynthesizer&);
    ~ReverbUI();

    void paint(Graphics&) override;
    void resized() override;

private:
    MFSynthesizer& processor;

    Slider size;
    Slider damping;
    Slider stereoWidth;
    Slider dry;
    Slider wet;
    Slider freeze;

    Label sizeLabel, dampingLabel, stereoWidthLabel, dryLabel, wetLabel, freezeLabel;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sizeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampingVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> stereoWidthVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freezeVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbUI)
};