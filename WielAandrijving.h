/**
 * @file WielAandrijving.h
 * @brief Declaratie van de WielAandrijving klasse voor motorbesturing.
 */

#ifndef WIELAANDRIJVING_H
#define WIELAANDRIJVING_H

#include <Zumo32U4.h>

/**
 * @class WielAandrijving
 * @brief Laag-niveau hardware-interface voor de motoren van de Zumo32U4.
 */
class WielAandrijving {
private:
    Zumo32U4Motors motors; ///< Hardware object voor de motoraansturing.

public:
    /**
     * @brief Stuurt de motoren direct aan met de opgegeven snelheden.
     * @param links Gewenste snelheid linker motor (-400 t/m 400).
     * @param rechts Gewenste snelheid rechter motor (-400 t/m 400).
     */
    void stuurMotoren(int links, int rechts);
};

#endif