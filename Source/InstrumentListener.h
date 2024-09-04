#pragma once

#include <JuceHeader.h>
#include "Instrument.h"  
#include "Oscillator.h"
#include "Filter.h"

class InstrumentListener : public juce::ComboBox::Listener {
public:
    InstrumentListener(Instrument& instrument, MFSynthesizer& processor)
        : instrumentComponent(instrument), processor(processor) {
        instrumentComponent.getInstruMenu().addListener(this);
    }

    ~InstrumentListener() {
        instrumentComponent.getInstruMenu().removeListener(this);
    }

    void InstrumentListener::comboBoxChanged(juce::ComboBox* comboBox) override {
        if (comboBox == &instrumentComponent.getInstruMenu()) {
            int selectedId = instrumentComponent.getInstruMenu().getSelectedId();
            int newWaveType1Value = 0;
            int newWaveType2Value = 0;
            float blendValue1 = 0.6f;
            float blendValue2 = 0.6f;
            float newAttackValue, newDecayValue, newSustainValue, newReleaseValue;
            int filterTypeVal = 0;
            float filterCutoff = 0;
            float filterRes = 0;
            float newSize, newdamp, newWideth, newDry, newWet, newFreeze;
            float  newpitchWheel = 0;
            float newtunableSemitone = 1;
            switch (selectedId) {
            case 1: // Guitar
                newWaveType1Value = 2; // Saw
                newWaveType2Value = 3; // Sine
                blendValue1 = 0.15f;
                blendValue2 = 0.3f;
                newAttackValue = 0.01f;
                newDecayValue = 0.01f;
                newSustainValue = 0.5f;
                newReleaseValue = 0.08f;
                filterTypeVal = 1;
                filterCutoff = 5000.0f;
                filterRes = 2.3f;
                newSize = 0.5f;
                newdamp = 0.5f;
                newWideth = 0.5f;
                newDry = 0.9f;
                newWet = 0.1f;
                newFreeze = 0.1f;
                newpitchWheel = 500.0f;
                newtunableSemitone = 1.0f;
                break;
            case 2: // Violin
                newWaveType1Value = 3; // Sine
                newWaveType2Value = 2; // Square
                blendValue1 = 0.2f;
                blendValue2 = 0.05f;
                newAttackValue = 0.5f;
                newDecayValue = 0.3f;
                newSustainValue = 0.75f;
                newReleaseValue = 0.8f;
                filterTypeVal = 1;
                filterCutoff = 5000.0f;
                filterRes = 2.0f;
                newSize = 0.1f;
                newdamp = 0.1f;
                newWideth = 0.1f;
                newDry = 0.9f;
                newWet = 0.1f;
                newFreeze = 0.1f;
                newpitchWheel = 500.0f;
                newtunableSemitone = 1.5f;
                break;
            case 3: // Piano
                newWaveType1Value = 1; // Square
                newWaveType2Value = 2; // Saw
                blendValue1 = 0.25f;
                blendValue2 = 0.05f;
                newAttackValue = 0.01f;
                newDecayValue = 0.01f;
                newSustainValue = 0.90f;
                newReleaseValue = 0.30f;
                filterTypeVal = 1;
                filterCutoff = 20000.0f;
                filterRes = 1.0f;
                newSize = 0.1f;
                newdamp = 0.2f;
                newWideth = 0.1f;
                newDry = 0.9f;
                newWet = 0.1f;
                newFreeze = 0.0f;
                break;
            default:
                break; 
            }
            processor.tree.getParameter("wavetype1")->setValueNotifyingHost(float(newWaveType1Value - 1) / 3.0f);
            processor.tree.getParameter("wavetype2")->setValueNotifyingHost(float(newWaveType2Value - 1) / 3.0f);
            processor.tree.getParameter("blend1")->setValueNotifyingHost(blendValue1/0.5);
            processor.tree.getParameter("blend2")->setValueNotifyingHost(blendValue2/0.5);
            processor.tree.getParameter("attack")->setValueNotifyingHost((newAttackValue-0.01) / 2.99f);
            processor.tree.getParameter("decay")->setValueNotifyingHost((newDecayValue-0.01) / 2.99f);
            processor.tree.getParameter("sustain")->setValueNotifyingHost(newSustainValue);
            processor.tree.getParameter("release")->setValueNotifyingHost((newReleaseValue-0.01) / 2.99f);
            processor.tree.getParameter("filterType")->setValueNotifyingHost(float(filterTypeVal - 1) / 2.0f);
            processor.tree.getParameter("filterCutoff")->setValueNotifyingHost((filterCutoff-20) / 19980.0f);
            processor.tree.getParameter("filterRes")->setValueNotifyingHost((filterRes-0.01)/ 4.99f);
            processor.tree.getParameter("size")->setValueNotifyingHost(newSize);
            processor.tree.getParameter("damping")->setValueNotifyingHost(newdamp);
            processor.tree.getParameter("stereoWidth")->setValueNotifyingHost(newWideth);
            processor.tree.getParameter("dry")->setValueNotifyingHost(newDry);
            processor.tree.getParameter("wet")->setValueNotifyingHost(newWet);
            processor.tree.getParameter("freeze")->setValueNotifyingHost(newFreeze);
            processor.tree.getParameter("pitchwheel")->setValueNotifyingHost((newpitchWheel+1000)/2000.0f);
            processor.tree.getParameter("tunablesemitone")->setValueNotifyingHost((newtunableSemitone-1)/11.0f);
        }
    }
private:
    Instrument& instrumentComponent;
    MFSynthesizer& processor;
};