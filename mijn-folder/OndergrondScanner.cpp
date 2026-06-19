/**
 * @file OndergrondScanner.cpp
 * @brief Hier regelen we het scannen van de vloer en het kalibreren.
 * @author Groep 2
 */

#include "OndergrondScanner.h"
#include <Arduino.h>

void OndergrondScanner::initialiseer() {
    hardwareSensoren.initFiveSensors();
}

void OndergrondScanner::kalibreer() {
    ledYellow(1);
    for (uint16_t meting = 0; meting < 800; meting++) {
        hardwareSensoren.calibrate();
    }
    ledYellow(0);
}

void OndergrondScanner::kalibreerStap() {
    hardwareSensoren.calibrate();
}

int16_t OndergrondScanner::leesLijn() {
    return hardwareSensoren.readLine(sensorMeetwaarden);
}

bool OndergrondScanner::isLijnKwijt() {
    for (uint8_t i = 0; i < 5; i++) {
        if (sensorMeetwaarden[i] > 100) { 
            return false;
        }
    }
    return true;
}

bool OndergrondScanner::isGroen() {
    uint16_t maxVal = 0;
    for (uint8_t i = 0; i < 5; i++) {
        if (sensorMeetwaarden[i] > maxVal) {
            maxVal = sensorMeetwaarden[i];
        }
    }
    
    Serial.print(" MaxSensor: ");
    Serial.print(maxVal);
    
    return maxVal < GROEN_DREMPEL;
}