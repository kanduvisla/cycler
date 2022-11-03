#ifndef CYCLER_H
#define CYCLER_H 

#include "definitions.h"

// Perform a single MIDI tick. Defaults to 24 PPQ
void cycler_tick();

// Get the channel used for polyphony. Channels with lower velocity are dropped first
byte cycler_get_next_polyphony_channel();

#endif