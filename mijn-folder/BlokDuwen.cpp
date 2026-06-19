/**
 * @file BlokDuwen.cpp
 * @brief De logica om objecten te zien en met een manoeuvre aan de kant te duwen.
 * @author Groep 2
 */

#include "BlokDuwen.h"
#include <Arduino.h>

BlokDuwen::BlokDuwen(WielAandrijving* wa) : motorSturing(wa) {
    // Klasse opstarten
}

void BlokDuwen::verwerkBlokken(int afstandDeel) {
    static bool objectGezien = false;
    static unsigned long actieStartTijd = 0;

    // Als we iets horen of zien dat te dichtbij komt (boven de 20), gaan we rammen
    if (afstandDeel > 20 && !objectGezien) {
        objectGezien = true;
        actieStartTijd = millis();
        Serial.println("Object gespot! Manoeuvre starten...");
    }

    if (objectGezien) {
        unsigned long verstrekenTijd = millis() - actieStartTijd;

        if (verstrekenTijd < 1500) {
            // Stap 1: Vol gas vooruit om het blok weg te duwen (1,5 seconde)
            motorSturing->stuurMotoren(350, 350);
        } 
        else if (verstrekenTijd < 2500) {
            // Stap 2: Even een stukje achteruit rijden om los te komen (1 seconde)
            motorSturing->stuurMotoren(-200, -200);
        } 
        else {
            // Stap 3: Klaar! Motoren uit en we kunnen weer stand-by staan
            motorSturing->stuurMotoren(0, 0);
            objectGezien = false;
            Serial.println("Manoeuve klaar. Blok is weg.");
        }
    }
}