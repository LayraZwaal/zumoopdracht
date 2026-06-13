/**
 * @file RobotRegelaar.h
 * @brief Declaratie van de hoofd-regelaar klasse (PID, Logica & Seriële besturing).
 */

#ifndef ROBOTREGELAAR_H
#define ROBOTREGELAAR_H

#include "WielAandrijving.h"
#include "OndergrondScanner.h"
#include "SnelheidsMeter.h"

/**
 * @class RobotRegelaar
 * @brief De hoofdklasse die de robotbesturing regelt op basis van sensor input en Seriële monitor commando's.
 * @details Past Dependency Injection toe om los te staan van de directe hardware implementaties.
 */
class RobotRegelaar {
private:
    WielAandrijving* aandrijving;     ///< Pointer naar de wielaandrijving.
    OndergrondScanner* scanner;       ///< Pointer naar de ondergroundscanner.
    SnelheidsMeter* teller;           ///< Pointer naar de snelheidsmeter (encoders).

    const int MAX_SPEED    = 400;     ///< Maximale PWM-waarde voor de motoren.
    const int CRUISE_SPEED = 350;     ///< Standaardsnelheid op het zwarte wegdek.
    const int GROEN_SPEED  = 180;     ///< Begrensde lagere snelheid voor op groene lijnen.

    const double CONSTANT_P = 0.75;   ///< Proportionele constante (Kp) voor de PID regelaar.
    const double CONSTANT_D = 1.55;   ///< Afgeleide constante (Kd) voor de PID regelaar.

    int lastError;                    ///< Slaat de fout van de vorige loop op ten behoeve van de D-actie.
    int bufferTeller;                 ///< Aantal resterende credits om over een stippellijn heen te skippen.
    
    bool automatischeModus;           ///< True = Automatisch lijnvolgen, False = Handmatig via Seriële Monitor.

    /**
     * @brief Handelt de handmatige besturing via seriële commando's af.
     * @param commando Karakter ontvangen via de USB interface ('w', 's', 'a', 'd', 'x').
     */
    void verwerkHandmatigCommando(char commando);

    /**
     * @brief Voert de automatische PID lijnvolg-algoritmen uit.
     */
    void voerAutomatischLijnvolgenUit();

public:
    /**
     * @brief Constructor voor de RobotRegelaar.
     * @param wa Pointer naar de WielAandrijving module.
     * @param os Pointer naar de OndergrondScanner module.
     * @param sm Pointer naar de SnelheidsMeter module.
     */
    RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm);

    /**
     * @brief Voert één cyclus van de besturingslogica uit.
     * @details Controleert op binnenkomende seriële data om te switchen van modus of de motoren handmatig te sturen.
     */
    void verwerkLoop();
};

#endif