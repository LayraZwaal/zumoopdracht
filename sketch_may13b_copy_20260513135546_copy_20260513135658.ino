#include <Wire.h>
#include <Zumo32U4.h>
#include "EncoderManagerr.h"

/**
 * @brief Encoder object van de Zumo32U4 robot.
 *
 * Dit object wordt gebruikt om de linker en rechter
 * encoderwaardes uit te lezen.
 */
Zumo32U4Encoders encoders;

/**
 * @brief EncoderManager object.
 *
 * Dit object beheert het uitlezen en verwerken van
 * encoderdata.
 */
EncoderManager encoderManager;

/**
 * @brief Setup functie.
 *
 * Wordt één keer uitgevoerd bij het opstarten van de Arduino.
 * Initialiseert de Serial communicatie en reset de encoders.
 */
void setup()
{
    Serial.begin(9600);

    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();

    Serial.println("Encoder systeem gestart");
}

/**
 * @brief Hoofdloop van het programma.
 *
 * Blijft continu draaien en:
 * - leest encoderdata uit
 * - print de data naar de Serial Monitor
 * - wacht 100ms tussen metingen
 */
void loop()
{
    encoderManager.update();
    encoderManager.printData();

    delay(100);
}