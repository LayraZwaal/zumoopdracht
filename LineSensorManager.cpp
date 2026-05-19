#include "LineSensorManager.h"
#include <Arduino.h>

/** @brief Constructor initialiseert de array op 0. */
LineSensorManager::LineSensorManager() {
    for (uint8_t i = 0; i < 5; i++) {
        _sensorValues[i] = 0;
    }
}

/** @brief Initialiseert de hardware pinnen voor de 5 sensoren. */
void LineSensorManager::init() {
    _lineSensors.initFiveSensors();
}

/** @brief Voert de kalibratie uit. */
void LineSensorManager::calibrate() {
    ledYellow(1);
    _display.clear();
    _display.print(F("Line cal"));

    for (uint16_t i = 0; i < 400; i++) {
        _lineSensors.calibrate();
    }

    ledYellow(0);
    _display.clear();
}

/** @brief Geeft de positie van de lijn terug (0-4000). */
int16_t LineSensorManager::getPosition() {
    return _lineSensors.readLine(_sensorValues);
}

/** @brief Print de huidige waarden naar de Seriële monitor voor debugging. */
void LineSensorManager::debugToSerial() {
    int16_t pos = getPosition();
    Serial.print("Lijn Positie: ");
    Serial.print(pos);
    Serial.print(" | Sensoren: ");
    for (uint8_t i = 0; i < 5; i++) {
        Serial.print(_sensorValues[i]);
        Serial.print(" ");
    }
    Serial.println();
}