#include <stdio.h>
#include "definitions.h"
#include "ads.h"

byte cycler_calculate_attack(integer currentPosition, integer totalLength, byte finalVolume) {
    if (totalLength == 0 || currentPosition >= totalLength) {
        return finalVolume;
    }

    float p = (float)currentPosition / (float)totalLength;
    return finalVolume * p;
}

byte cycler_calculate_volume(integer currentPosition, integer attackValue, integer decayValue, integer sustainValue) {
    if (currentPosition >= attackValue || attackValue == 0) {
        return sustainValue >> 3;
    }

    if (decayValue == 0) {
        // Get percentage of currentPosition / totalLength
        float p = (float)currentPosition / (float)attackValue;
        return integer(sustainValue * p) >> 3;
    }

    // We have a Decay value to work with, so we need to split our time frame in 2:
    integer attackValue1 = attackValue / 2;
    integer attackValue2 = attackValue / 2;

    // For debugging:
    int precision = 4;
    printf("\n");
    printf("Current Position = %u\n", currentPosition);
    printf("Attack           = %u\n", attackValue);
    printf("Attack Value 1   = %u\n", attackValue1);
    printf("Attack Value 2   = %u\n", attackValue2);
    printf("Decay            = %u\n", decayValue);
    printf("Sustain          = %u\n", sustainValue);

    if (currentPosition <= attackValue1) {
        // Calculate the total decay value:
        float dP = (float)decayValue / (float)1024;
        integer dV = (1023 - sustainValue); // * dP;

        printf("Decay Percentage = %6.*lf\n", precision, dP);
        printf("Decay Value      = %u\n", dV);

        // We're on the left side (or on top) of the slope:
        float p = (float)currentPosition / (float)attackValue1;
        printf("Percentage = %6.*lf\n", precision, p);
        return (sustainValue + dV) * p;
    } else {
        // We're on the right side (or on the end) of the slope:

    }

    return 0;
}