#include <stdio.h>
#include "definitions.h"
#include "ads.h"

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
    printf("CP = %u\n", currentPosition);
    printf("A  = %u\n", attackValue);
    printf("A1 = %u\n", attackValue1);
    printf("A2 = %u\n", attackValue2);
    printf("D  = %u\n", decayValue);
    printf("S  = %u\n", sustainValue);

    if (currentPosition <= attackValue1) {
        // Calculate the total decay value:
        float dP = (float)decayValue / (float)1024;
        integer dV = (1023 - sustainValue); // * dP;

        printf("DP = %6.*lf\n", precision, dP);
        printf("DV = %u\n", dV);

        // We're on the left side (or on top) of the slope:
        float p = (float)currentPosition / (float)attackValue1;
        printf("P  = %6.*lf\n", precision, p);
        return (sustainValue + dV) * p;
    } else {
        // We're on the right side (or on the end) of the slope:

    }

    return 0;
}