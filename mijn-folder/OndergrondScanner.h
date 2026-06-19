/**
 * @file OndergrondScanner.h
 * @brief Header file voor de sensorbalk onder de robot.
 * @author Groep 2
 */

#ifndef ONDERGRONDSCANNER_H
#define ONDERGRONDSCANNER_H

#include <Zumo32U4.h>

class OndergrondScanner {
private:
    Zumo32U4LineSensors hardwareSensoren; ///< De echte sensoren van de Zumo bieb
    uint16_t sensorMeetwaarden[5];        ///< Array om de ruwe data (0-1000) in op te slaan
    const int GROEN_DREMPEL = 500;        ///< Kantelpunt om te checken of we op groen rijden

public:
    void initialiseer();
    void kalibreer();
    void kalibreerStap(); ///< Fixes voor als we handmatig met de knop willen kalibreren
    int16_t leesLijn();
    bool isLijnKwijt();
    bool isGroen();
};

#endif // ONDERGRONDSCANNER_H