/**
 * @file RobotRegelaar.cpp
 * @brief Implementatie van de RobotRegelaar klasse inclusief PID-, buffer- en handmatige USB-besturing.
 */

#include "RobotRegelaar.h"
#include <Arduino.h>
#include <Wire.h>

RobotRegelaar::RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm) 
    : aandrijving(wa), scanner(os), teller(sm) {
    lastError = 0;
    bufferTeller = 6; // Start met de 6 ingestelde stippellijn credits.
    automatischeModus = true; // De robot start standaard in automatische modus.
}

void RobotRegelaar::verwerkLoop() {
    // Check of er via de USB-kabel (Seriële Monitor) data binnenkomt
    if (Serial.available() > 0) {
        char ontvangenInvoer = Serial.read();
        
        // Modus-switch knop ('m')
        if (ontvangenInvoer == 'm') { 
            automatischeModus = !automatischeModus;
            aandrijving->stuurMotoren(0, 0); // Veiligheid: stop motoren direct bij wisselen
            if(automatischeModus) {
                Serial.println("Modus gewijzigd: AUTOMATISCH (Lijnvolgen)");
            } else {
                Serial.println("Modus gewijzigd: HANDMATIG (Toetsenbordbesturing)");
            }
        } 
        
        // Als we in handmatige modus zitten, stuur de invoer direct door naar de motoren
        if (!automatischeModus) {
            verwerkHandmatigCommando(ontvangenInvoer);
        }
    }

    // Voer continu de geselecteerde modus uit
    if (automatischeModus) {
        voerAutomatischLijnvolgenUit();
    }
}

void RobotRegelaar::verwerkHandmatigCommando(char commando) {
    switch (commando) {
        case 'w': // Vooruit
            aandrijving->stuurMotoren(250, 250);
            Serial.println("Handmatig: Vooruit");
            break;
        case 's': // Achteruit
            aandrijving->stuurMotoren(-250, -250);
            Serial.println("Handmatig: Achteruit");
            break;
        case 'a': // Linksaf draaien op de plaats
            aandrijving->stuurMotoren(-200, 200);
            Serial.println("Handmatig: Linksaf");
            break;
        case 'd': // Rechtsaf draaien op de plaats
            aandrijving->stuurMotoren(200, -200);
            Serial.println("Handmatig: Rechtsaf");
            break;
        case 'x': // Noodstop
            aandrijving->stuurMotoren(0, 0);
            Serial.println("Handmatig: STOP");
            break;
        default:
            // Bij een onbekende toets doen we niks om plotselinge schokken te voorkomen
            break;
    }
}

void RobotRegelaar::voerAutomatischLijnvolgenUit() {
    int16_t position = scanner->leesLijn();

    // --- STIPPELLIJN HANDLING ---
    if (scanner->isLijnKwijt()) {
        if (bufferTeller > 0) {
            bufferTeller--;
            int speedDiff = lastError / 6;
            int left = constrain(220 + speedDiff, -MAX_SPEED, MAX_SPEED);
            int right = constrain(220 - speedDiff, -MAX_SPEED, MAX_SPEED);
            aandrijving->stuurMotoren(left, right);
            return;
        }
        aandrijving->stuurMotoren(200, 200);
        return;
    }

    bufferTeller = 6;

    // --- PID BEREKENING ---
    int error = 2000 - position;
    double Yp = CONSTANT_P * error;
    double Yd = (error - lastError) * CONSTANT_D;
    lastError = error;

    int output = Yp + Yd;

    // --- SNELHEIDSBEPALING: groen = langzamer, zwart = normaal ---
    int snelheid = scanner->isGroen() ? GROEN_SPEED : CRUISE_SPEED;

    // Dynamisch afremmen op basis van de fout (scherpte van de bocht)
    snelheid = snelheid - (abs(error) / 10);
    snelheid = constrain(snelheid, 80, CRUISE_SPEED);

    // Actuatorsnelheden berekenen middels de PID-output
    int leftSpeed  = constrain(snelheid - output, -MAX_SPEED, MAX_SPEED);
    int rightSpeed = constrain(snelheid + output, -MAX_SPEED, MAX_SPEED);

    aandrijving->stuurMotoren(leftSpeed, rightSpeed);
}