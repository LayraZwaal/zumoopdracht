/**
 * @file RobotRegelaar.h
 * @brief Definitie van de centrale besturingsmodule voor de Zumo robot.
 */

#ifndef ROBOTREGELAAR_H
#define ROBOTREGELAAR_H

#include "WielAandrijving.h"
#include "OndergrondScanner.h"
#include "SnelheidsMeter.h"

/**
 * @class RobotRegelaar
 * @brief Coördineert de robotbewegingen op basis van sensorgegevens en seriële input.
 * @details Maakt gebruik van Dependency Injection voor een losgekoppelde architectuur.
 */
class RobotRegelaar {
private:
    WielAandrijving* motorSturing;       ///< Toegang tot de wielmotoren.
    OndergrondScanner* bodemScanner;    ///< Toegang tot de reflectiesensoren.
    SnelheidsMeter* rotatieTeller;      ///< Toegang tot de wiel-encoders.

    const int SNELHEID_MAXIMAAL = 400;  ///< Maximale PWM-waarde voor de motoraansturing.
    const int SNELHEID_CRUISE   = 350;  ///< Basissnelheid op een donker wegdek.
    const int SNELHEID_GROEN    = 180;  ///< Gereduceerde snelheid bij groene detectie.

    const double FACTOR_PROPORTIONEEL = 0.75; ///< Kp-waarde voor de koerscorrectie.
    const double FACTOR_AFGELEIDE     = 1.55; ///< Kd-waarde voor de koerscorrectie.

    int vorigeAfwijking;                ///< Onthoudt de afwijking uit de vorige cyclus (D-actie).
    int stippellijnTegoed;              ///< Resterende bufferslagen tijdens een onderbroken lijn.
    
    bool isAutonoomActief;              ///< Schakelaar tussen automatische lijnvolging en handmatige invoer.

    /**
     * @brief Verwerkt binnenkomende navigatiecommando's vanuit de pc.
     * @param commandoKarakter Commando via de USB-poort ('w', 's', 'a', 'd', 'x').
     */
    void hanteerHandmatigeInvoer(char commandoKarakter);

    /**
     * @brief Start het automatische PD-algoritme om de lijn te volgen.
     */
    void voerLijnvolgAlgoritmeUit();

public:
    /**
     * @brief Constructor voor de centrale RobotRegelaar.
     * @param wa Pointer naar de WielAandrijving module.
     * @param os Pointer naar de OndergrondScanner module.
     * @param sm Pointer naar de SnelheidsMeter module.
     */
    RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm);

    /**
     * @brief Hoofdloop-functie die continu wordt aangeroepen vanuit de hoofd-sketch.
     */
    void verwerkLoop();
};

#endif // ROBOTREGELAAR_H