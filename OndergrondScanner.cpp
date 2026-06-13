/**
 * @file OndergrondScanner.cpp
 * @brief Implementatie van de OndergrondScanner klasse.
 */

#include "OndergrondScanner.h"
#include <Arduino.h>

void OndergrondScanner::initialiseer() {
    lineSensors.initFiveSensors();
}

void OndergrondScanner::kalibreer() {
    ledYellow(1);
    for (uint16_t i = 0; i < 800; i++) {
        lineSensors.calibrate();
    }
    ledYellow(0);
}

int16_t OndergrondScanner::leesLijn() {
    return lineSensors.readLine(lineSensorValues);
}

bool OndergrondScanner::isLijnKwijt() {
    for (uint8_t i = 0; i < 5; i++) {
        if (lineSensorValues[i] > 100) return false;
    }
    return true;
}

bool OndergrondScanner::isGroen() {
    uint16_t maxVal = 0;
    for (uint8_t i = 0; i < 5; i++) {
        if (lineSensorValues[i] > maxVal) maxVal = lineSensorValues[i];
    }
    return maxVal < GROEN_DREMPEL;
}