/*
    This is an example, which defaults to a 6-voice polyphony mode (mode 1), with a fixed attack slope of 1 beat.
*/

#include <cycler.h>
#include <MIDI.h>

const int analogPin0 = A0;
const int analogPin1 = A1;

// Change this settings to play with the attack slope:
int attackDuration = 96;    // = 24 ppqn * 4 notes = 1 beat
int finalVolume = 64;       

MIDI_CREATE_DEFAULT_INSTANCE();

// Tested on an Arduino Nano
void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    // Register our note with Cycler.
    // Cycler will give us the next free channel, that we can use to pass the information through:
    byte channel = cycler_note_on(inNote, inVelocity);
    MIDI.sendNoteOn(inNote, inVelocity, channel);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    // If it's a note off, we need to inform cycler that there is a note off.
    // Cycler will return the channel that was assigned, so we can pass it through:
    byte channel = cycler_note_off(inNote);
    MIDI.sendNoteOff(inNote, inVelocity, channel);
}

void setup()
{
    // Register note handlers
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    // Launch MIDI, listening to channel 1.
    MIDI.begin(1); 
    MIDI.turnThruOff();

    // Initialize Cycler:
    cycler_set_mode(CYCLER_MODE_6_POLY);
}

void loop()
{
    if (MIDI.read()) {
        switch(MIDI.getType()) {
            case midi::Clock:       
                // If it is a Clock tick, we need to inform Cycler that there has been a clock tick.
                cycler_tick();
                
                // Check if there are attack slopes that require updating:
                if (attackDuration > 0 && finalVolume > 0) {
                    for (int channel = 0; channel < 6; channel += 1) {
                        if (notePlaying[channel] == true && playingTicks[channel] <= attackDuration) {
                            byte volume = cycler_calculate_attack(playingTicks[channel], attackDuration, finalVolume);
                            MIDI.sendControlChange(7, volume, channel);  // Volume CC=7
                        }
                    }
                }

                break;
        }
    }
}
