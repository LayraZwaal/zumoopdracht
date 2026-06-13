/**
 * @file RobotRegelaar.cpp
 * @brief Uitwerking van de robotbesturing met autonome PD-regeling en handmatige overschakeling.
 */

#include "RobotRegelaar.h"
#include <Arduino.h>
#include <Wire.h>

RobotRegelaar::RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm) 
    : motorSturing(wa), bodemScanner(os), rotatieTeller(sm) {
    vorigeAfwijking = 0;
    stippellijnTegoed = 6;         // Startwaarde voor de stippellijn-buffer.
    isAutonoomActief = true;       // De robot start standaard in de automatische stand.
}

void RobotRegelaar::verwerkLoop() {
    // Controleren of er instructies klaarstaan in de Seriële Monitor via USB
    if (Serial.available() > 0) {
        char toetsInvoer = Serial.read();
        
        // Wisselen van modus via de 'm'-toets
        if (toetsInvoer == 'm') { 
            isAutonoomActief = !isAutonoomActief;
            motorSturing->stuurMotoren(0, 0); // Noodstop voor veiligheid tijdens omschakelen
            
            if (isAutonoomActief) {
                Serial.println("Systeemstatus: AUTONOOM (Lijn volgen)");
            } else {
                Serial.println("Systeemstatus: HANDMATIG (Besturing via toetsenbord)");
            }
        }
        
        // Als we handmatig sturen, sturen we de toets direct door naar de verwerker
        if (!isAutonoomActief && toetsInvoer != 'm') {
            hanteerHandmatigeInvoer(toetsInvoer);
        }
    }

    // Indien autonoom, voer de sensoren- en motorlus uit
    if (isAutonoomActief) {
        voerLijnvolgAlgoritmeUit();
    }
}

void RobotRegelaar::hanteerHandmatigeInvoer(char invoerKarakter) {
    switch (invoerKarakter) {
        case 'w': // Recht naar voren rijden
            motorSturing->stuurMotoren(250, 250);
            break;
        case 's': // Achteruit rijden
            motorSturing->stuurMotoren(-250, -250);
            break;
        case 'a': // Om de as naar links roteren
            motorSturing->stuurMotoren(-200, 200);
            break;
        case 'd': // Om de as naar rechts roteren
            motorSturing->stuurMotoren(200, -200);
            break;
        case 'x': // Onmiddellijke stopactie
            motorSturing->stuurMotoren(0, 0);
            break;
        default:
            // Onbekende invoer negeren om haperingen te voorkomen
            break;
    }
}

void RobotRegelaar::voerLijnvolgAlgoritmeUit() {
    int16_t sensorPositie = bodemScanner->leesLijn();

    // --- LOGICA VOOR ONDERBROKEN LIJNEN (STIPPELLIJN) ---
    if (bodemScanner->isLijnKwijt()) {
        if (stippellijnTegoed > 0) {
            stippellijnTegoed--;
            // Schat de bocht in op basis van de laatst bekende koersafwijking
            int correctieMarge = vorigeAfwijking / 6;
            int linksSnelheid  = constrain(220 + correctieMarge, -SNELHEID_MAXIMAAL, SNELHEID_MAXIMAAL);
            int rechtsSnelheid = constrain(220 - correctieMarge, -SNELHEID_MAXIMAAL, SNELHEID_MAXIMAAL);
            motorSturing->stuurMotoren(linksSnelheid, rechtsSnelheid);
            return;
        }
        // Buffer is leeg: rustig rechtuit blijven rijden in de hoop de lijn te hervinden
        motorSturing->stuurMotoren(200, 200);
        return;
    }

    // Reset het stippellijn-tegoed zodra er weer een lijn gedetecteerd is
    stippellijnTegoed = 6;

    // --- MATHEMATISCHE PD-BEREKENING ---
    int huidigeAfwijking = 2000 - sensorPositie; 
    double proportioneleActie = FACTOR_PROPORTIONEEL * huidigeAfwijking;
    double afgeleideActie     = (huidigeAfwijking - vorigeAfwijking) * FACTOR_AFGELEIDE;
    vorigeAfwijking = huidigeAfwijking;

    int totaleStuurCorrectie = proportioneleActie + afgeleideActie;

    // --- REGULERING VAN DE SNELHEID (Groene zone detectie) ---
    int basisSnelheid = bodemScanner->isGroen() ? SNELHEID_GROEN : SNELHEID_CRUISE;

    // Snelheidsdemping toepassen in scherpe bochten om slippen tegen te gaan
    int dempingsFactor = abs(totaleStuurCorrectie) / 4;
    int gecorrigeerdeSnelheid = basisSnelheid - dempingsFactor;
    if (gecorrigeerdeSnelheid < 100) gecorrigeerdeSnelheid = 100; // Ondergrens behouden

    // Bereken het uiteindelijke vermogen per wielmotor
    int motorLinks  = constrain(gecorrigeerdeSnelheid - totaleStuurCorrectie, -SNELHEID_MAXIMAAL, SNELHEID_MAXIMAAL);
    int motorRechts = constrain(gecorrigeerdeSnelheid + totaleStuurCorrectie, -SNELHEID_MAXIMAAL, SNELHEID_MAXIMAAL);

    // Stuur de berekende waarden naar de wielaandrijving
    motorSturing->stuurMotoren(motorLinks, motorRechts);
}