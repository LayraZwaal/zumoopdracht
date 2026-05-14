#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ProximitySensors proxSensors;

void setup() {
//maakserieleverbinding voor uitlezing
  Serial.begin(9600);
  // initializeerd senors(links rech en midde, gebruik alleen middelste senosr
  proxSensors.initThreeSensors(); 
}

void loop() {
  // Pulse the LEDs and read the sensors
  proxSensors.read();
// geeft een waarde
  uint8_t links   = proxSensors.countsFrontWithLeftLeds();
  uint8_t rechs  = proxSensors.countsFrontWithRightLeds();
// print de verwerkte sensor waarde voor de sensor
  Serial.println(" L: "); Serial.print(links);
  Serial.print(" R: "); Serial.print(rechs);

  delay(100);
}