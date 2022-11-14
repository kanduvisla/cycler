#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"
#include "cycler.h"

// MARK: --- Assertion methods

// Assert if X equals Y
void assert(byte x, byte y, char* message) {
    if (x != y) {
        printf("\n\033[0;31mFAIL:\033[0m expected %u, got %u \033[0;34m(%s)\033[0m\n", x, y, message);
    } else {
        printf(".");
    }
}

// Assert if arr contains X
void assert_contains(byte arr[], size_t arr_size, byte x, char* message) {
    bool ok = false;
    for (size_t i = 0; i < arr_size; i++) {
        if (arr[i] == x) {
            ok = true;
        }
    }
    if (ok == false) {
        printf("\n\033[0;31mFAIL:\033[0m not found in array: %u \033[0;34m(%s)\033[0m\n", x, message);
    } else {
        printf(".");
    }
}

// MARK: --- Helper methods

byte cycler_note_on_and_tick(byte note, byte velocity) {
    byte channel = cycler_note_on(note, velocity);
    cycler_tick();
    return channel;
}

byte cycler_note_off_and_tick(byte note) {
    byte channel = cycler_note_off(note);
    cycler_tick();
    return channel + 1;
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
    cycler_note_on_and_tick(10, 100);
    cycler_note_on_and_tick(60, 100);
    cycler_note_on_and_tick(20, 100);
    cycler_note_on_and_tick(30, 100);
    byte channelNote4 = cycler_note_on_and_tick(40, 100);
    cycler_note_on_and_tick(50, 100);
    // The channel that plys note 4 goes off first:
    cycler_note_off_and_tick(40);
    cycler_note_off_and_tick(30);
    cycler_note_off_and_tick(50);
    cycler_note_off_and_tick(20);
    test_polyphony_channel(channelNote4);
    cycler_reset();
}

// Test 3/3 polyphony
void test_polyphony_3_3() {
    // Scenario: note below C5 returns channel 1...3, note above C5 returns channel 4...6

    // Setup:
    cycler_reset();
    cycler_set_mode(CYCLER_MODE_3_3_POLY);

    // Exercise:
    byte channelNote1 = cycler_note_on_and_tick(48, 100);   // 48 = C4
    byte channelNote2 = cycler_note_on_and_tick(60, 100);   // 60 = C5
    byte channelNote1_2 = cycler_note_on_and_tick(50, 90);  // 50 = D4
    byte channelNote2_2 = cycler_note_on_and_tick(62, 90);  // 62 = D5
    byte channelNote1_3 = cycler_note_on_and_tick(52, 80);  // 52 = E4
    byte channelNote2_3 = cycler_note_on_and_tick(64, 80);  // 64 = E5

    // Verify:
    byte leftArr[] = { 1, 2, 3 };
    byte rightArr[] = { 4, 5, 6 };
    assert_contains(leftArr, 3, channelNote1, "note should play on channel 1...3");
    assert_contains(leftArr, 3, channelNote1_2, "note should play on channel 1...3");
    assert_contains(leftArr, 3, channelNote1_3, "note should play on channel 1...3");
    assert_contains(rightArr, 3, channelNote2, "note should play on channel 4...6");
    assert_contains(rightArr, 3, channelNote2_2, "note should play on channel 4...6");
    assert_contains(rightArr, 3, channelNote2_3, "note should play on channel 4...6");

    // Extra notes:
    byte freeChannel1 = cycler_note_off_and_tick(50);
    byte freeChannel2 = cycler_note_off_and_tick(62);
    byte newChannel1 = cycler_note_on_and_tick(32, 80);
    byte newChannel2 = cycler_note_on_and_tick(72, 80);
    assert(freeChannel1, newChannel1, "New note should play on newly free low channel");
    assert(freeChannel2, newChannel2, "New note should play on newly free high channel");
}

// Test 3/1 polyphony
void test_polyphony_3_1() {
    // Scenario: note below C5 returns channel 1...3, note above C5 always returns channel 4

    // Setup:
    cycler_reset();
    cycler_set_mode(CYCLER_MODE_3_1_POLY);

    // Exercise:
    byte channelNote1 = cycler_note_on_and_tick(48, 100);   // 48 = C4
    byte channelNote2 = cycler_note_on_and_tick(60, 100);   // 60 = C5
    byte channelNote1_2 = cycler_note_on_and_tick(50, 90);  // 50 = D4
    byte channelNote2_2 = cycler_note_on_and_tick(62, 90);  // 62 = D5
    byte channelNote1_3 = cycler_note_on_and_tick(52, 80);  // 52 = E4
    byte channelNote2_3 = cycler_note_on_and_tick(64, 80);  // 64 = E5

    // Verify:
    byte leftArr[] = { 1, 2, 3 };
    byte rightArr[] = { 4 };
    assert_contains(leftArr, 3, channelNote1, "note should play on channel 1...3");
    assert_contains(leftArr, 3, channelNote1_2, "note should play on channel 1...3");
    assert_contains(leftArr, 3, channelNote1_3, "note should play on channel 1...3");
    assert(4, channelNote2, "note should play on channel 4");
    assert(4, channelNote2_2, "note should play on channel 4");
    assert(4, channelNote2_3, "note should play on channel 4");

    // Extra notes:
    byte freeChannel1 = cycler_note_off_and_tick(50);
    cycler_note_off_and_tick(62);
    byte newChannel1 = cycler_note_on_and_tick(32, 80);
    byte newChannel2 = cycler_note_on_and_tick(72, 80);
    assert(freeChannel1, newChannel1, "New note should play on newly free low channel");
    assert(4, newChannel2, "New note should play on newly free high channel");
}

// Test 4 polyphony
void test_polyphony_4() {
    // Scenario: notes returns channel 1...4, never 5 or 6

    // Setup:
    cycler_reset();
    cycler_set_mode(CYCLER_MODE_3_1_POLY);

    // Exercise:
    byte channelNote1 = cycler_note_on_and_tick(48, 100);   // 48 = C4
    byte channelNote2 = cycler_note_on_and_tick(60, 100);   // 60 = C5
    byte channelNote1_2 = cycler_note_on_and_tick(50, 90);  // 50 = D4
    byte channelNote2_2 = cycler_note_on_and_tick(62, 90);  // 62 = D5
    byte channelNote1_3 = cycler_note_on_and_tick(52, 80);  // 52 = E4
    byte channelNote2_3 = cycler_note_on_and_tick(64, 80);  // 64 = E5

    // Verify:
    byte channelArr[] = { 1, 2, 3, 4 };
    assert_contains(channelArr, 4, channelNote1, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote1_2, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote1_3, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote2, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote2_2, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote2_3, "note should play on channel 1...4");

    // Extra notes:
    cycler_note_off_and_tick(50);
    cycler_note_off_and_tick(60);
    cycler_note_off_and_tick(64);
    byte newChannel1 = cycler_note_on_and_tick(30, 100);
    byte newChannel2 = cycler_note_on_and_tick(50, 100);
    byte newChannel3 = cycler_note_on_and_tick(80, 100);
    byte newChannel4 = cycler_note_on_and_tick(70, 100);
    assert_contains(channelArr, 4, newChannel1, "note should play on channel 1...4");
    assert_contains(channelArr, 4, newChannel2, "note should play on channel 1...4");
    assert_contains(channelArr, 4, newChannel3, "note should play on channel 1...4");
    assert_contains(channelArr, 4, newChannel4, "note should play on channel 1...4");
}

// Test 4/1 polyphony
void test_polyphony_4_1() {
    // Scenario: note below C5 returns channel 1...4, note above C5 always returns channel 5

    // Setup:
    cycler_reset();
    cycler_set_mode(CYCLER_MODE_4_1_POLY);

    // Exercise:
    byte channelNote1 = cycler_note_on_and_tick(48, 100);   // 48 = C4
    byte channelNote2 = cycler_note_on_and_tick(60, 100);   // 60 = C5
    byte channelNote1_2 = cycler_note_on_and_tick(50, 90);  // 50 = D4
    byte channelNote2_2 = cycler_note_on_and_tick(62, 90);  // 62 = D5
    byte channelNote1_3 = cycler_note_on_and_tick(52, 80);  // 52 = E4
    byte channelNote2_3 = cycler_note_on_and_tick(64, 80);  // 64 = E5

    // Verify:
    byte channelArr[] = { 1, 2, 3, 4 };
    assert_contains(channelArr, 4, channelNote1, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote1_2, "note should play on channel 1...4");
    assert_contains(channelArr, 4, channelNote1_3, "note should play on channel 1...4");
    assert(5, channelNote2, "note should play on channel 5");
    assert(5, channelNote2_2, "note should play on channel 5");
    assert(5, channelNote2_3, "note should play on channel 5");

    // Extra notes:
    cycler_note_off_and_tick(50);
    cycler_note_off_and_tick(62);
    byte newChannel1 = cycler_note_on_and_tick(32, 80);
    byte newChannel2 = cycler_note_on_and_tick(72, 80);
    assert_contains(channelArr, 4, newChannel1, "New note should play on newly free low channel");
    assert(5, newChannel2, "New note should play on newly free high channel");
}

// MARK: --- Main application

int main(void) {
    test_polyphony();
    test_polyphony_3_3();
    test_polyphony_3_1();
    test_polyphony_4();
    test_polyphony_4_1();
    printf("\n");
    return 0;
}
