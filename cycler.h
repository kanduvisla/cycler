#ifndef CYCLER_H
#define CYCLER_H 

#include "definitions.h"

// Reset everything
void cycler_reset();

// Perform a single MIDI tick. Defaults to 24 PPQ
void cycler_tick();

// Get the channel used for polyphony. Channels with lower velocity are dropped first
byte cycler_get_next_polyphony_channel();

// Register a note on with Cycler
void cycler_note_on(byte note, byte vel, byte channel);

// Register a note off with Cycler
void cycler_note_off(byte note);

#endif