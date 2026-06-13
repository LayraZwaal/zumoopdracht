/**
 * @file SnelheidsMeter.cpp
 * @brief Implementatie van de SnelheidsMeter klasse.
 */

#include "SnelheidsMeter.h"

int16_t SnelheidsMeter::leesEncoderLinks() {
    return encoders.getCountsLeft();
}

int16_t SnelheidsMeter::leesEncoderRechts() {
    return encoders.getCountsRight();
}