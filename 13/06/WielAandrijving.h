/**
 * @file WielAandrijving.h
 * @brief Declaratie van de module die de motoraansturing van de Zumo robot verzorgt.
 */

#ifndef WIELAANDRIJVING_H
#define WIELAANDRIJVING_H

#include <Zumo32U4.h>

/**
 * @class WielAandrijving
 * @brief Directe interface naar de fysieke motoren van het Zumo-platform.
 */
class WielAandrijving {
private:
    Zumo32U4Motors hardwareMotoren; ///< Het bibliotheek-object voor de motoren.

public:
    /**
     * @brief Wijzigt de rotatiesnelheid van beide rupsbanden direct.
     * @param links PWM-waarde voor de linkerzijde (-400 tot 400).
     * @param rechts PWM-waarde voor de rechterzijde (-400 tot 400).
     */
    void stuurMotoren(int links, int rechts);
};

#endif // WIELAANDRIJVING_H