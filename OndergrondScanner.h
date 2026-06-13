/**
 * @file OndergrondScanner.h
 * @brief Declaratie van de OndergrondScanner klasse voor de Zumo32U4 sensoren.
 */

#ifndef ONDERGRONDSCANNER_H
#define ONDERGRONDSCANNER_H

#include <Zumo32U4.h>

/**
 * @class OndergrondScanner
 * @brief Klasse verantwoordelijk voor het inlezen en interpreteren van de 5 lijnsensoren.
 */
class OndergrondScanner {
private:
    Zumo32U4LineSensors lineSensors;       ///< Hardware object van de Zumo32U4 bibliotheek.
    uint16_t lineSensorValues[5];          ///< Array om de ruwe sensorwaarden (0-1000) in op te slaan.
    const int GROEN_DREMPEL = 500;         ///< Drempelwaarde waaronder een lijn als groen wordt gezien.

public:
    /**
     * @brief Initialiseert de 5 lijnsensoren van de Zumo.
     */
    void initialiseer();

    /**
     * @brief Voert de kalibratieroutine uit.
     * @details Laat het gele LEDje branden en kalibreert de sensoren 800 keer.
     */
    void kalibreer();

    /**
     * @brief Leest de positie op de lijn uit.
     * @return int16_t De positie ten opzichte van de lijn (0 t/m 4000, waarbij 2000 het midden is).
     */
    int16_t leesLijn();

    /**
     * @brief Controleert of de robot de lijn volledig kwijt is (stippellijn of kruispunt).
     * @return true als alle sensoren onder de reflectiewaarde van 100 zitten, anders false.
     */
    bool isLijnKwijt();

    /**
     * @brief Controleert of de robot momenteel op een groene lijn rijdt.
     * @return true als de hoogst gemeten sensorwaarde onder de GROEN_DREMPEL ligt.
     */
    bool isGroen();
};

#endif