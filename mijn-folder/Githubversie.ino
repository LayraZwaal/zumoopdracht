/**
 * @file JouwHoofdBestand.ino
 * @brief Dit is het startpunt van onze Zumo32U4 robot. [cite: 1, 2]
 * @author Groep 2
 */

#include <Wire.h>
#include <Zumo32U4.h>
#include "WielAandrijving.h"
#include "OndergrondScanner.h"
#include "SnelheidsMeter.h"
#include "RobotRegelaar.h"

// Hier maken we de verschillende onderdelen van de robot aan
WielAandrijving aandrijving; 
OndergrondScanner scanner;   
SnelheidsMeter meter;
// We gooien de onderdelen in de hoofdregelaar zodat die alles kan aansturen [cite: 3]
RobotRegelaar regelaar(&aandrijving, &scanner, &meter);

/**
 * @brief De setup die Arduino één keer runt bij het opstarten. [cite: 4]
 */
void setup() {
  Serial.begin(9600);
  // Sensoren even aanzetten en kalibreren op de baan [cite: 5]
  scanner.initialiseer();
  scanner.kalibreer();
}

/**
 * @brief De oneindige loop die de robot aan de gang houdt. [cite: 6]
 */
void loop() {
  regelaar.verwerkLoop();
}