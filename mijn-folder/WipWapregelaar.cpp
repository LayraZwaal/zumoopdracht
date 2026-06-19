/**
 * @file WipWapRegelaar.cpp
 * @brief Implementatie van de wipwap-balanssturing.
 */

#include "WipWapRegelaar.h"
#include <Zumo32U4.h>

WipWapRegelaar::WipWapRegelaar(WielAandrijving* wa) 
    : motorSturing(wa), isVoltooid(false) {}

void WipWapRegelaar::resetStatus() {
    isVoltooid = false;
}

bool WipWapRegelaar::isWipWapVoltooid() {
    return isVoltooid;
}

void WipWapRegelaar::verwerkWippen(float huidigePitch) {
    isVoltooid = false;
    int herstelVertraging = 500;

    // Als de robot achterover helt (pitch > 0.1), stuur hem achteruit om te corrigeren
    if (huidigePitch > 0.1) {
        motorSturing->stuurMotoren(-200, -200);
        delay(150); 
        motorSturing->stuurMotoren(0, 0);
        delay(herstelVertraging);
    } 
    // Als de robot voorover helt (pitch < -0.1), stuur hem vooruit om te corrigeren
    else if (huidigePitch < -0.1) {
        motorSturing->stuurMotoren(200, 200);
        delay(150); 
        motorSturing->stuurMotoren(0, 0);
        delay(herstelVertraging);
    }

    // Als de robot nagenoeg horizontaal staat, controleer of hij 5 seconden stabiel blijft
    if (huidigePitch > -0.1 && huidigePitch < 0.1) {
        unsigned long doelTijd = millis() + 5000;
        bool stabielGebleven = true;
        
        while (millis() < doelTijd) {
            // Live de IMU opnieuw uitlezen tijdens het wachten
            Zumo32U4IMU liveImu;
            liveImu.readAcc();
            float livePitch = atan2(liveImu.a.x, liveImu.a.z);

            // Als hij tijdens het wachten toch weer begint te kantelen, breek de timer af
            if (livePitch <= -0.1 || livePitch >= 0.1) {
                stabielGebleven = false;
                break;
            }
            delay(10); // Korte pauze tegen overbelasting van de processor
        }

        // Als de robot de volle 5 seconden horizontaal heeft gestaan, is de opdracht voltooid
        if (stabielGebleven) {
            isVoltooid = true;
            motorSturing->stuurMotoren(0, 0);
            Serial.println("WipWap succesvol voltooid! Robot staat stabiel.");
        }
    }
}