/**
 * @file   Githubversie.ino
 * @brief Dit is het startpunt van onze Zumo32U4 robot. 
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
// We gooien de onderdelen in de hoofdregelaar zodat die alles kan aansturen 
RobotRegelaar regelaar(&aandrijving, &scanner, &meter);

/**
 * @brief De setup die Arduino één keer runt bij het opstarten. 
 */
void setup() {
  Serial.begin(9600);
  // Sensoren even aanzetten en kalibreren op de baan 
  scanner.initialiseer();
  scanner.kalibreer();
}

/**
 * @brief De oneindige loop die de robot aan de gang houdt. 
 */
void loop() {
  regelaar.verwerkLoop();
}
