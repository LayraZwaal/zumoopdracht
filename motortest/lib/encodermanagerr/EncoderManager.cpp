#include "EncoderManagerr.h"

// externe encoder van Zumo
extern Zumo32U4Encoders encoders;

/**
 * @brief Constructor van EncoderManager.
 *
 * Initialiseert de encoderwaarden op 0.
 */
EncoderManager::EncoderManager()
{
    leftCount = 0;
    rightCount = 0;
    previousLeft = 0;
    previousRight = 0;
}

/**
 * @brief Update encoderwaarden.
 *
 * Slaat de vorige waarden op en leest daarna de nieuwe
 * encoderwaarden uit de Zumo32U4 encoders.
 */
void EncoderManager::update()
{
    previousLeft = leftCount;
    previousRight = rightCount;

    leftCount = encoders.getCountsLeft();
    rightCount = encoders.getCountsRight();
}

/**
 * @brief Print encoderdata naar Serial Monitor.
 *
 * Toont:
 * - totale linker encoderwaarde
 * - totale rechter encoderwaarde
 * - verandering (delta) sinds vorige meting
 */
void EncoderManager::printData()
{
    Serial.print("Links totaal: ");
    Serial.print(leftCount);

    Serial.print(" | Rechts totaal: ");
    Serial.print(rightCount);

    Serial.print(" | Links delta: ");
    Serial.print(leftCount - previousLeft);

    Serial.print(" | Rechts delta: ");
    Serial.println(rightCount - previousRight);
}
int EncoderManager::getLeftCount()
{
    return leftCount;
}
int EncoderManager::getRightCount()
{
    return rightCount;
}