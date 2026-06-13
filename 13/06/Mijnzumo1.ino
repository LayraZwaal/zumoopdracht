/**
 * @file MijnZumoProject.ino
 * @brief Hoofdbestand voor de aansturing van de Zumo32U4 robot.
 * @details Dit bestand initialiseert de hardwarecomponenten via Dependency Injection
 * en tikt in de oneindige loop constant de RobotRegelaar aan.
 * @author Groep 2 Emirhan
 * @date 11 juni 2026
 */

#include <Wire.h>
#include "WielAandrijving.h"
#include "OndergrondScanner.h"
#include "SnelheidsMeter.h"
#include "RobotRegelaar.h"

/// @brief Object voor de fysieke motorbesturing.
WielAandrijving   mijnMotoren;

/// @brief Object voor het beheren en uitlezen van de 5 lijnsensoren.
OndergrondScanner mijnSensoren;

/// @brief Object voor het meten van de gereden snelheid en afstand via encoders.
SnelheidsMeter    mijnSnelheidsMeter;

/// @brief De centrale hersenen van de robot die sensoren en actuatoren koppelt.
RobotRegelaar     regelaar(&mijnMotoren, &mijnSensoren, &mijnSnelheidsMeter);

/**
 * @brief Initialisatie van de Arduino en de hardware componenten.
 * @details Start de seriële communicatie op USB-niveau, initialiseert de sensoren 
 * en voert de automatische kalibratieroutine uit.
 */
void setup() {
  Serial.begin(9600);
  
  mijnSensoren.initialiseer();
  mijnSensoren.kalibreer();
}

/**
 * @brief De hoofdloop van het programma.
 * @details Wordt continu achter elkaar uitgevoerd en delegeert de volledige
 * afhandeling (scannen, rekenen, sturen) naar de verwerkLoop van de regelaar.
 */
void loop() {
  regelaar.verwerkLoop();
}