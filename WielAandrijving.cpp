/**
 * @file WielAandrijving.cpp
 * @brief Implementatie van de WielAandrijving klasse.
 */

#include "WielAandrijving.h"

void WielAandrijving::stuurMotoren(int links, int rechts) {
    motors.setSpeeds(links, rechts);
}