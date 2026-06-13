/**
 * @file SnelheidsMeter.h
 * @brief Declaratie van de module voor het registreren van wielrotaties via de encoders.
 */

#ifndef SNELHEIDSMETER_H
#define SNELHEIDSMETER_H

#include <Zumo32U4.h>

/**
 * @class SnelheidsMeter
 * @brief Module die de encoder-tellingen van de linker- en rechterwielen bijhoudt.
 */
class SnelheidsMeter {
private:
    Zumo32U4Encoders hardwareEncoders; ///< Het bibliotheek-object voor de wiel-encoders.

public:
    /**
     * @brief Vraagt de actuele tellerstand op van het linker wiel.
     * @return int16_t Totaal aantal geregistreerde pulsen sinds de start/reset.
     */
    int16_t leesEncoderLinks();

    /**
     * @brief Vraagt de actuele tellerstand op van het rechter wiel.
     * @return int16_t Totaal aantal geregistreerde pulsen sinds de start/reset.
     */
    int16_t leesEncoderRechts();
};

#endif // SNELHEIDSMETER_H