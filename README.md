# MF Synthesizer Plugin

## Overview
The **MF Synthesizer** is a multifunctional synthesizer developed using the JUCE framework. It is designed to help users create and manipulate sounds across various instruments with ease. The plugin includes multiple sound manipulation modules such as instrument selection, waveform control, ADSR parameters, filters, and reverbs, making it a versatile tool for music production.

## Features
- **Instrument Selection**: Choose from a variety of instruments. Upon selection, the plugin automatically adjusts other sound parameters to suit the selected instrument.
- **Waveform Control**: Customize the waveform type for your sound.
- **ADSR Envelope**: Fine-tune the attack, decay, sustain, and release of the sound to achieve desired timbral characteristics.
- **Filter and Reverb Modules**: Apply various filters and reverb effects to enhance the sound output.
- **Five Synth Voices**: The synthesizer can handle up to five MIDI signals simultaneously.

## How It Works
- The **InstrumentListener** class automatically adjusts the synthesizer's settings based on the selected instrument.
- The backend processes MIDI signals, generates frequencies, and applies ADSR gain and effects like filtering and reverb to the signal.
- The **ADSR** envelope generator modifies the sound's shape and dynamics over time, allowing for precise sound sculpting.

## Installation
1. Clone or download the repository.
2. Open the project in your JUCE environment.
3. Compile the project and use the synthesizer in your preferred DAW as a VST3 plugin.

## Usage
- Select an instrument from the instrument menu.
- Adjust waveform, ADSR, and other settings to customize the sound.
- Play MIDI signals to generate audio output through the plugin.
