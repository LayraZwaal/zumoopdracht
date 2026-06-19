/**
 * @file WielAandrijving.h
 * @brief Header voor de motorsturing van de robot.
 * @author Groep 2
 */

#ifndef WIELAANDRIJVING_H
#define WIELAANDRIJVING_H

#include <Zumo32U4.h>

class WielAandrijving {
private:
    Zumo32U4Motors hardwareMotoren; ///< De echte motoren van de Zumo bibliotheek
public:
    WielAandrijving() = default;
    void stuurMotoren(int links, int rechts);
};

#endif