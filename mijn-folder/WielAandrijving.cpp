/**
 * @file WielAandrijving.cpp
 * @brief Dit bestand stuurt de motoren direct aan.
 * @author Groep 2
 */

#include "WielAandrijving.h"

void WielAandrijving::stuurMotoren(int links, int rechts) {
    // Snelheid direct doorsturen naar de motoren van de Zumo
    hardwareMotoren.setSpeeds(links, rechts);
}