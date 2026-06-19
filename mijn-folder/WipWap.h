/**
 * @file WipWap.h
 * @brief Declaratie van de WipWap klasse met een rustige aanloopsnelheid.
 */

#ifndef WIPWAP_H
#define WIPWAP_H

#include <Arduino.h>
#include "WielAandrijving.h"
#include "SnelheidsMeter.h"

class WipWap {
private:
    WielAandrijving* motorSturing;
    SnelheidsMeter* rotatieTeller;

    unsigned long wipStartTijd;
    unsigned long grijsWachtStartTijd;
    float hoogstePitch;
    
    bool isAfgerond;
    bool heeftGrijsGezien;
    bool isAanHetWachtenOpGrijs;

    const int SNELHEID_WIP = 90; // Rustig kruipen over de zwarte lijn om grijs te spotten

public:
    WipWap(WielAandrijving* wa, SnelheidsMeter* sm);
    void startWipSessie();
    void verwerkWip(float huidigePitch, bool isLijnGrijs);
    bool isWipKlaar();
};

#endif // WIPWAP_H