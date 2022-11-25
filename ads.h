#ifndef CYCLER_ADS_H
#define CYCLER_ADS_H 

#include "definitions.h"

/// @brief Calculate the volume according to some parameters
/// @param currentPosition
/// @param totalLength
/// @param attackValue
/// @param decayValue 
/// @param sustainValue 
/// @return the calculated volume
byte calculateVolume(integer currentPosition, integer totalLength, byte attackValue, byte decayValue, byte sustainValue);

#endif