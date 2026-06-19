/**
 * @file RobotRegelaar.cpp
 * @brief De logica achter het autonoom rijden, de PID en handmatige besturing.
 * @author Groep 2
 */

#include "RobotRegelaar.h"
#include <Arduino.h>
#include <Wire.h>

RobotRegelaar::RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm) 
    : motorSturing(wa), bodemScanner(os), rotatieTeller(sm) { // WipWapRegelaar hier weggehaald
    laatsteMeting = 2000;
    vorigeAfwijking = 0;
    foutSom = 0;
    onderbrekingTeller = 6; 
    isAutonoomActief = true;      
    modusWipWapActief = false; 
}

void RobotRegelaar::verwerkLoop() {
    if (Serial.available() > 0) {
        char toetsInvoer = Serial.read();
        
        if (toetsInvoer == 'm') {
            isAutonoomActief = !isAutonoomActief;
            motorSturing->stuurMotoren(0, 0); 
            
            if (isAutonoomActief) {
                Serial.println("Systeemstatus: AUTONOOM (Lijn volgen)");
            } else {
                Serial.println("Systeemstatus: HANDMATIG");
            }
        }

        if (toetsInvoer == 'w') {
            // Modus kan niet geactiveerd worden omdat de WipWap module nu buitenspel staat
            Serial.println("Modus: WIPWAP tijdelijk niet beschikbaar.");
        }
        
        if (!isAutonoomActief && toetsInvoer != 'm' && toetsInvoer != 'w') {
            hanteerHandmatigeInvoer(toetsInvoer);
        }
    }

    if (isAutonoomActief) {
        // We skippen de wipwap-check en rijden gewoon puur op de PID-lijnvolger
        corrigeerKoersOpBaan(); 
    }
}

void RobotRegelaar::hanteerHandmatigeInvoer(char commandoKarakter) {
    switch (commandoKarakter) {
        case 'i': motorSturing->stuurMotoren(250, 250); break; 
        case 's': motorSturing->stuurMotoren(-250, -250); break;
        case 'a': motorSturing->stuurMotoren(-150, 150); break;
        case 'd': motorSturing->stuurMotoren(150, -150); break;
        case 'x': motorSturing->stuurMotoren(0, 0); break;
    }
}

void RobotRegelaar::corrigeerKoersOpBaan() {
    int16_t sensorPositie = bodemScanner->leesLijn();

    // --- Stippellijn opvangen zodat 'ie niet crasht ---
    if (bodemScanner->isLijnKwijt()) {
        if (onderbrekingTeller > 0) {
            onderbrekingTeller--;
            return; 
        } else {
            motorSturing->stuurMotoren(200, 200);
            vorigeAfwijking = 0;
            foutSom = 0;
            return;
        }
    }

    onderbrekingTeller = 6;
    laatsteMeting = sensorPositie;

    // --- De PID Berekening ---
    int huidigeAfwijking = 2000 - sensorPositie;
    double pBijdrage = VERSTERKING_P * huidigeAfwijking;
    foutSom += huidigeAfwijking;
    double iBijdrage = foutSom * VERSTERKING_I;
    double dBijdrage = (huidigeAfwijking - vorigeAfwijking) * VERSTERKING_D;
    vorigeAfwijking = huidigeAfwijking;

    int stuurCorrectie = pBijdrage + iBijdrage + dBijdrage;

    // --- Snelheid bepalen (rustig aan bij groen) ---
    int basisSnelheid = bodemScanner->isGroen() ? SNELHEID_GROEN : SNELHEID_CRUISE;

    int linksInstelling  = constrain(basisSnelheid - stuurCorrectie, -SNELHEID_MAX, SNELHEID_MAX);
    int rechtsInstelling = constrain(basisSnelheid + stuurCorrectie, -SNELHEID_MAX, SNELHEID_MAX);

    motorSturing->stuurMotoren(linksInstelling, rechtsInstelling);

    Serial.print("Pos: ");
    Serial.print(sensorPositie);
    Serial.print(" L: ");
    Serial.print(linksInstelling);
    Serial.print(" R: ");
    Serial.println(rechtsInstelling);
}