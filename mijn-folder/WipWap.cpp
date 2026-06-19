/**
 * @file WipWap.cpp
 * @brief Rustig oprijden, exact 2 seconden stoppen bij grijs en daarna doorrijden.
 */

#include "WipWap.h"

WipWap::WipWap(WielAandrijving* wa, SnelheidsMeter* sm) 
    : motorSturing(wa), rotatieTeller(sm) {
    wipStartTijd = 0;
    grijsWachtStartTijd = 0;
    hoogstePitch = -90.0f;
    isAfgerond = false;
    heeftGrijsGezien = false;
    isAanHetWachtenOpGrijs = false;
}

void WipWap::startWipSessie() {
    wipStartTijd = millis();
    grijsWachtStartTijd = 0;
    hoogstePitch = -90.0f;
    isAfgerond = false;
    heeftGrijsGezien = false;
    isAanHetWachtenOpGrijs = false;
}

void WipWap::verwerkWip(float huidigePitch, bool isLijnGrijs) {
    if (isAfgerond) {
        return;
    }

    // --- FASE 1: RUSTIG DE WIP OPRIJDEN OP ZOEK NAAR GRIJS ---
    if (!heeftGrijsGezien && !isAanHetWachtenOpGrijs) {
        motorSturing->stuurMotoren(SNELHEID_WIP, SNELHEID_WIP);

        if (isLijnGrijs) {
            isAanHetWachtenOpGrijs = true;
            grijsWachtStartTijd = millis();
            Serial.println("[WipWap] Grijze lijn gezien! Stoppen...");
        }
        return;
    }

    // --- FASE 2: EXACT 2 SECONDEN VOLLEDIG STILSTAAN ---
    if (isAanHetWachtenOpGrijs) {
        motorSturing->stuurMotoren(0, 0); 
        
        if (millis() - grijsWachtStartTijd >= 2000) { 
            isAanHetWachtenOpGrijs = false;
            heeftGrijsGezien = true;
            wipStartTijd = millis(); 
            Serial.println("[WipWap] 2 seconden voorbij. We rijden door!");
        }
        return; 
    }

    // --- FASE 3: NA DE STOP 1,5 SECONDE DOORRIJDEN OVER DE WIP ---
    unsigned long doorrijdTijd = millis() - wipStartTijd;
    if (doorrijdTijd < 1500) {
        motorSturing->stuurMotoren(150, 150);
    } else {
        isAfgerond = true;
        Serial.println("[WipWap] WipWap voltooid. Terug naar lijnvolgen.");
    }
}

bool WipWap::isWipKlaar() {
    return isAfgerond;
}