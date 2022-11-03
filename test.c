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
        printf("%s", message);
    } else {
        printf(".");
    }
}

// MARK: --- Test cases for Cycler

void test_polyphony() {
    // Setup:

    // Exercise:

    // Verify:
    
}

// MARK: --- Main application

int main(void) {
    test_polyphony();
    return 0;
}
