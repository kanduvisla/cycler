#include <stdio.h>
#include "test.h"

// All notes are coming in on one MIDI channel
// These are then spread out over multiple MIDI out channels, dropping velocity first

unsigned char note_in = 0;  // MIDI note input
unsigned char vel_in  = 0;  // MIDI velocity input

// MIDI note + velocity output
unsigned char ch1_note_out = 0;
unsigned char ch1_vel_out = 0;
unsigned char ch2_note_out = 0;
unsigned char ch2_vel_out = 0;
unsigned char ch3_note_out = 0;
unsigned char ch3_vel_out = 0;
unsigned char ch4_note_out = 0;
unsigned char ch4_vel_out = 0;
unsigned char ch5_note_out = 0;
unsigned char ch5_vel_out = 0;
unsigned char ch6_note_out = 0;
unsigned char ch6_vel_out = 0;

int main(void) {
    run_tests();
    return 0;
}

// Single MIDI tick
void tick() {

}