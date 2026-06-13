/**
 * @file SnelheidsMeter.h
 * @brief Declaratie van de SnelheidsMeter klasse voor encoder-uitlezing.
 */

#ifndef SNELHEIDSMETER_H
#define SNELHEIDSMETER_H

#include <Zumo32U4.h>

/**
 * @class SnelheidsMeter
 * @brief Klasse verantwoordelijk voor het bijhouden van de wiel-encoders en afstand.
 */
class SnelheidsMeter {
private:
    Zumo32U4Encoders encoders; ///< Hardware object voor de wiel-encoders.

public:
    /**
     * @brief Geeft het aantal tikken van de linker encoder terug.
     * @return int16_t Aantal counts sinds de laatste reset.
     */
    int16_t leesEncoderLinks();

    /**
     * @brief Geeft het aantal tikken van de rechter encoder terug.
     * @return int16_t Aantal counts sinds de laatste reset.
     */
    int16_t leesEncoderRechts();
};

#endif