/**
 * @file WielAandrijving.cpp
 * @brief Implementatie van de directe motorsturing.
 */

#include "WielAandrijving.h"

void WielAandrijving::stuurMotoren(int links, int rechts) {
    // Geef de PWM-signalen rechtstreeks door aan de hardware-as
    hardwareMotoren.setSpeeds(links, rechts);
}