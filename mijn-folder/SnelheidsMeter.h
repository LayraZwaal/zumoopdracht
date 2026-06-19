/**
 * @file SnelheidsMeter.h
 * @brief Header voor het uitlezen van de wiel-encoders.
 * @author Groep 2
 */

#ifndef SNELHEIDSMETER_H
#define SNELHEIDSMETER_H

#include <Zumo32U4.h>

class SnelheidsMeter {
private:
    Zumo32U4Encoders encoders; ///< De fysieke encoders van de robot
public:
    SnelheidsMeter() = default;
    int32_t pakAfstandLinks();
    int32_t pakAfstandRechts();
    void resetTellers();
};

#endif