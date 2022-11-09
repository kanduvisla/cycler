#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"
#include "cycler.h"

// MARK: --- Assertion methods

// void assert_uc(unsigned char x, unsigned char y, char* message) {

// }

// #define assert(x, y) _Generic((x, y), unsigned char: assert_uc)(x, y, message)

void assert(byte x, byte y, char* message) {
    if (x != y) {
        printf("\n\033[0;31mFAIL:\033[0m expected %u, got %u \033[0;34m(%s)\033[0m\n", x, y, message);
    } else {
        printf(".");
    }
}

// MARK: --- Test cases for Cycler

static void test_polyphony_channel(byte expectedChannel) {
    byte result = cycler_get_next_polyphony_channel();
    assert(expectedChannel, result, "incorrect output channel");
    cycler_reset();
}

// Polyphony testing
void test_polyphony() {
    // Scenario #1: First note returns first free channel (fresh setup)
    test_polyphony_channel(6);

    // Scenario #2: A note is played on channel 6:
    cycler_note_on(60, 100);
    test_polyphony_channel(5);

    // Scenario #3: A note is played on channel 5 & 6:
    cycler_note_on(50, 100);
    cycler_note_on(60, 100);
    test_polyphony_channel(4);

    // Scenario #4: Only channel 1 is free:
    cycler_note_on(10, 100);
    cycler_note_on(20, 100);
    cycler_note_on(40, 100);
    cycler_note_on(50, 100);
    cycler_note_on(60, 100);
    test_polyphony_channel(1);
    
    // Scenario #5: Channel 1 & 6 are used, channel 4 has the longest idle time
    cycler_note_on(10, 100);
    cycler_tick();
    cycler_note_on(60, 100);
    cycler_tick();
    cycler_note_on(20, 100);
    cycler_tick();
    cycler_note_on(30, 100);
    cycler_tick();
    byte channelNote4 = cycler_note_on(40, 100);
    cycler_tick();
    cycler_note_on(50, 100);
    cycler_tick();
    // The channel that plys note 4 goes off first:
    cycler_note_off(40);
    cycler_tick();
    cycler_note_off(30);
    cycler_tick();
    cycler_note_off(50);
    cycler_tick();
    cycler_note_off(20);
    cycler_tick();
    test_polyphony_channel(channelNote4);
    cycler_reset();
}

// Test 3/3 polyphony
void test_polyphony_3_3() {
    // Scenario #1: note below C5 returns channel 3, note above C5 returns channel 6
    // C5=byte 60
    cycler_reset();
    byte channelNote1 = cycler_note_on(48, 100); // 48 = C4
    byte channelNote2 = cycler_note_on(60, 100); // 60 = C5
    byte expectedChannel1 = 3;
    byte expectedChannel2 = 6;
    assert(expectedChannel1, channelNote1, "C4 should play on channel 3");
    assert(expectedChannel2, channelNote2, "C5 should play on channel 6");
}

// MARK: --- Main application

int main(void) {
    test_polyphony();
    test_polyphony_3_3();    
    printf("\n");
    return 0;
}
