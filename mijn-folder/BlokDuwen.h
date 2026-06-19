/**
 * @file BlokDuwen.h
 * @brief Header voor de module die blokken detecteert en wegschuift.
 * @author Groep 2
 */

#ifndef BLOKDUWEN_H
#define BLOKDUWEN_H

#include "WielAandrijving.h"

class BlokDuwen {
private:
    WielAandrijving* motorSturing; ///< Linkje naar de motoren om gas te kunnen geven

public:
    /**
     * @brief De constructor om de motorsturing aan deze klasse te koppelen.
     */
    BlokDuwen(WielAandrijving* wa);
    
    /**
     * @brief Hier checken we of er een object in de weg staat en bepalen we de actie.
     */
    void verwerkBlokken(int afstandDeel);
};

#endif // BLOKDUWEN_H