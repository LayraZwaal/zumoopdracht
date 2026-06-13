/**
 * @file SnelheidsMeter.cpp
 * @brief Uitwerking van de encoder-uitleesfuncties.
 */

#include "SnelheidsMeter.h"

int16_t SnelheidsMeter::leesEncoderLinks() {
    return hardwareEncoders.getCountsLeft();
}

int16_t SnelheidsMeter::leesEncoderRechts() {
    return hardwareEncoders.getCountsRight();
}