
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Instrument : public Component
{
public:
    Instrument(MFSynthesizer&);
    ~Instrument();

    void paint(Graphics&) override;
    void resized() override;

    juce::ComboBox& getInstruMenu() { return instruMenu; }

private:

    ComboBox instruMenu;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> instruSelection;

    MFSynthesizer& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Instrument)
};