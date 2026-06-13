/**
 * @file OndergrondScanner.h
 * @brief Declaratie van de optische sensorbalk voor het detecteren van de wegbaan.
 */

#ifndef ONDERGRONDSCANNER_H
#define ONDERGRONDSCANNER_H

#include <Zumo32U4.h>

/**
 * @class OndergrondScanner
 * @brief Beheert de vijf ingebouwde reflectiesensoren aan de onderzijde van de robot.
 */
class OndergrondScanner {
private:
    Zumo32U4LineSensors hardwareSensoren;     ///< Het bibliotheek-object voor de infraroodsensoren.
    uint16_t sensorMeetwaarden[5];            ///< Opslagbuffer voor de actuele reflectiewaarden (0-1000).
    const int GRENSWAARDE_GROEN = 500;        ///< Maximale waarde om een zone als groen te markeren.

public:
    /**
     * @brief Configureert de sensorbalk voor het gebruik van 5 actieve sensoren.
     */
    void initialiseer();

    /**
     * @brief Start de omgevingskalibratie.
     * @details Activeert de gele indicator en voert 800 opeenvolgende metingen uit.
     */
    void kalibreer();

    /**
     * @brief Bepaalt de exacte positie van de robot ten opzichte van de lijn.
     * @return int16_t Een waarde tussen 0 en 4000 (2000 vertegenwoordigt het exacte midden).
     */
    int16_t leesLijn();

    /**
     * @brief Controleert of de robot het contact met het zwarte spoor volledig heeft verloren.
     * @return true als er geen lijn wordt gezien, anders false.
     */
    bool isLijnKwijt();

    /**
     * @brief Controleert of de sensoren momenteel over een groen wegvlak rijden.
     * @return true bij groen-detectie, anders false.
     */
    bool isGroen();
};

#endif // ONDERGRONDSCANNER_H