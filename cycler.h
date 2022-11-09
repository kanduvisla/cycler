#ifndef CYCLER_H
#define CYCLER_H 

#include "definitions.h"

// Set the mode to run Cycler in
void cycler_set_mode(int mode);

// Reset everything
void cycler_reset();

// Perform a single MIDI tick. Defaults to 24 PPQ
void cycler_tick();

// Get the channel used for polyphony. Channels with lower velocity are dropped first
byte cycler_get_next_polyphony_channel();

// Register a note on with Cycler, it will return the channel that needs to be used
byte cycler_note_on(byte note, byte vel);

// Register a note off with Cycler and return the channel that was used
byte cycler_note_off(byte note);

#endif