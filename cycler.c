#include "cycler.h"

// All notes are coming in on one MIDI channel
// These are then spread out over multiple MIDI out channels, dropping velocity first

unsigned char note_in = 0;  // MIDI note input
unsigned char vel_in  = 0;  // MIDI velocity input

// MIDI notes are unsigned chars 0-127 = Midi note 128-255 = velocity

// MIDI note + velocity output
unsigned char channels[6];
// unsigned char ch1_note_out = 0;
// unsigned char ch1_vel_out = 0;
// unsigned char ch2_note_out = 0;
// unsigned char ch2_vel_out = 0;
// unsigned char ch3_note_out = 0;
// unsigned char ch3_vel_out = 0;
// unsigned char ch4_note_out = 0;
// unsigned char ch4_vel_out = 0;
// unsigned char ch5_note_out = 0;
// unsigned char ch5_vel_out = 0;
// unsigned char ch6_note_out = 0;
// unsigned char ch6_vel_out = 0;

// Single MIDI tick
void cycler_tick() {
    // TODO
}

unsigned char cycler_get_note(unsigned char input) {
    return 0;
}

unsigned char cycler_get_velocity(unsigned char input) {
    return 0;
}

unsigned char cycler_get_next_polyphony_channel(unsigned char channel, unsigned char velocity) {
    return 0;
}