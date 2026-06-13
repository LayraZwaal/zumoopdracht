/**
 * @file OndergrondScanner.cpp
 * @brief Implementatie van de kalibratie- en meetlogica van de sensorbalk.
 */

#include "OndergrondScanner.h"
#include <Arduino.h>

void OndergrondScanner::initialiseer() {
    // Initialiseer exact Silicon Labs-sensoren op de balk
    hardwareSensoren.initFiveSensors();
}

void OndergrondScanner::kalibreer() {
    ledYellow(1); // Zet de gele ingebouwde LED aan tijdens het inlezen van wit/zwart uitersten
    for (uint16_t meting = 0; meting < 800; meting++) {
        hardwareSensoren.calibrate();
    }
    ledYellow(0); // Schakel de LED weer uit wanneer de kalibratie voltooid is
}

int16_t OndergrondScanner::leesLijn() {
    // Vult de array aan met nieuwe data en geeft de berekende positie terug
    return hardwareSensoren.readLine(sensorMeetwaarden);
}

bool OndergrondScanner::isLijnKwijt() {
    // Als alle sensoren een zeer lage reflectie (lichte ondergrond) meten, is er geen lijn
    for (uint8_t i = 0; i < 5; i++) {
        if (sensorMeetwaarden[i] > 100) {
            return false; 
        }
    }
    return true;
}

bool OndergrondScanner::isGroen() {
    uint16_t hoogsteMeting = 0;
    // Zoek naar de piekwaarde binnen de huidige sensorarray
    for (uint8_t i = 0; i < 5; i++) {
        if (sensorMeetwaarden[i] > hoogsteMeting) {
            hoogsteMeting = sensorMeetwaarden[i];
        }
    }
    // Als zelfs de hoogste waarde onder de drempel blijft, rijden we op een groene ondergrond
    return hoogsteMeting < GRENSWAARDE_GROEN;
}