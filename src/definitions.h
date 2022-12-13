#ifndef CYCLER_DEFS_H
#define CYCLER_DEFS_H 

#include <inttypes.h>

// Type definitions
typedef uint8_t byte;

// Mode definitions
#define CYCLER_MODE_NONE 0
#define CYCLER_MODE_6_POLY 1
#define CYCLER_MODE_3_3_POLY 2
#define CYCLER_MODE_3_1_POLY 3
#define CYCLER_MODE_4_POLY 4
#define CYCLER_MODE_4_1_POLY 5
#define CYCLER_MODE_DUAL_1 6
#define CYCLER_MODE_DUAL_2 7
#define CYCLER_MODE_DUAL_3 8
#define CYCLER_MODE_TRIPLE_1 9
#define CYCLER_MODE_TRIPLE_2 10
#define CYCLER_MODE_BERSERK 11

#define CYCLER_MODE_MAX 12  // used to check the last mode

#endif