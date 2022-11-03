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
        printf("\033[0;31mFAIL:\033[0m expected %u, got %u \033[0;34m(%s)\033[0m\n", x, y, message);
    } else {
        printf(".");
    }
}

// MARK: --- Test cases for Cycler

void test_polyphony() {
    // Scenario #1: First note returns first free channel (fresh setup)
    byte expectedOutputChannel = 6;
    byte result = cycler_get_next_polyphony_channel();
    assert(expectedOutputChannel, result, "incorrect output channel");

    // Scenario #2: Some notes are played:
    
}

// MARK: --- Main application

int main(void) {
    test_polyphony();
    printf("\n");
    return 0;
}
