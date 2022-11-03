#include <stdio.h>
#include <stdbool.h>
#include "cycler.h"
#include "definitions.h"

// All notes are coming in on one MIDI channel
// These are then spread out over multiple MIDI out channels, dropping velocity first

// MIDI note per channel
byte notes[6] = {0};

// is the channel currently playing a note?
bool notePlaying[6] = {false};

// MIDI velocity per channel. When all channels are playing a note, the channel with the lowest velocity is sacrificed
byte velocity[6] = {0};

// The amount of idle ticks. When a channel is not playing a note, the channel that has been off the longest has the highest preference
uint16_t idleTicks[6] = {0};

// Increase the idle counter on the channels
static void increase_idle_counter() {
    for (int channel = 0; channel < 6; channel += 1) {
        if (notePlaying[channel] == false) {
            idleTicks[channel] += 1;
        }
    }
}

void cycler_reset() {
    for (byte channel = 0; channel < 6; channel += 1) {
        notes[channel] = 0;
        notePlaying[channel] = false;
        velocity[channel] = 0;
        idleTicks[channel] = 0;
    }
}

// Single MIDI tick
void cycler_tick() {
    increase_idle_counter();
}

// Get the next polyphony channel
byte cycler_get_next_polyphony_channel() {
    byte count = 0;
    byte returnChannel = 0;
    byte channel = 0;

    // First filter out channels that are not playing a note:
    for (channel = 0; channel < 6; channel += 1) {
        if (notePlaying[channel] == false) {
            count += 1;
            returnChannel = channel + 1;
        }
    }

    // If only one channel is returned, return that channel:
    if (count == 1) {
        return returnChannel;
    }

    // If multiple channels are returned, return the one with the longest idle time:
    if (count > 0) {
        uint16_t maxIdleTicks = 0;
        for (channel = 0; channel < 6; channel += 1) {
            if (notePlaying[channel] == false) {
                if (idleTicks[channel] > maxIdleTicks) {
                    maxIdleTicks = idleTicks[channel];
                    returnChannel = channel + 1;
                }
            }
        }
        return returnChannel;
    }

    // If no channels are returned (all channels are playing a note), return the one with the lowest velocity:
    byte minVelocity = 255;
    for (channel = 0; channel < 6; channel += 1) {
        if (velocity[channel] < minVelocity) {
            minVelocity = velocity[channel];
            returnChannel = channel + 1;
        }
    }

    // This will never happen:
    return returnChannel;
}

// Register a note on with cycler
void cycler_note_on(byte note, byte vel, byte channel) {
    notePlaying[channel - 1] = true;
    notes[channel - 1] = note;
    velocity[channel - 1] = vel;
    idleTicks[channel - 1] = 0;
}

// Register a note off with cycler
void cycler_note_off(byte note) {
    for (byte channel = 0; channel < 6; channel += 1) {
        if (notes[channel] == note) {
            notePlaying[channel] = false;
            notes[channel] = 0;
            velocity[channel] = 0;
            idleTicks[channel] = 0;
            return;
        }
    }
}