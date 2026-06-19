/**
 * @file SnelheidsMeter.cpp
 * @brief De logica om de wielomwentelingen (encoders) bij te houden.
 * @author Groep 2
 */

#include "SnelheidsMeter.h"

int32_t SnelheidsMeter::pakAfstandLinks() {
    return encoders.getCountsLeft();
}

int32_t SnelheidsMeter::pakAfstandRechts() {
    return encoders.getCountsRight();
}

void SnelheidsMeter::resetTellers() {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
}