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
byte cycler_calculate_volume(integer currentPosition, integer attackValue, integer decayValue, integer sustainValue);

/// @brief Calculate the volume according to some parameters
byte cycler_calculate_attack(integer currentPosition, integer totalLength, byte finalVolume);

#endif