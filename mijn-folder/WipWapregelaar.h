/**
 * @file WipWapRegelaar.h
 * @brief Declaratie van de WipWapRegelaar klasse conform jouw voertuigbesturing.
 */

#ifndef WIPWAPREGELAAR_H
#define WIPWAPREGELAAR_H

#include <Arduino.h>
#include "WielAandrijving.h"

class WipWapRegelaar {
private:
    WielAandrijving* motorSturing; ///< Dependency injection voor de motoren
    bool isVoltooid;               ///< Vlag die aangeeft of het wippen klaar is

public:
    /**
     * @brief Constructor die de motorsturing koppelt.
     */
    WipWapRegelaar(WielAandrijving* wa);

    /**
     * @brief Voert de wipwap-logica uit op basis van de meegegeven pitch (helling).
     * @param huidigePitch De actuele hellingshoek van de IMU.
     */
    void verwerkWippen(float huidigePitch);

    /**
     * @brief Controleert of de wipwap-actie is afgerond.
     * @return true als de robot stabiel is geweest en de actie klaar is.
     */
    bool isWipWapVoltooid();
    
    /**
     * @brief Reset de status zodat de wipwap opnieuw geactiveerd kan worden.
     */
    void resetStatus();
};

#endif // WIPWAPREGELAAR_H