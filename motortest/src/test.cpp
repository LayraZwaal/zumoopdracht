#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "EncoderManagerr.h"
#include "motorclass.h"

 motorclass motors;
EncoderManager encoders;
void setup() {
  Serial.begin(9600);
  // Initialiseer de motoren en encoders
 
}

void loop() {
  // Update de encoderwaarden
  motors.moveZumo(); // Zorg ervoor dat de Zumo beweegt zodat de encoders waarden kunnen veranderen
  delay(10000);
  motors.stopZumo();
  encoders.update();
  
  // Print de encoderdata naar Serial Monitor
  encoders.printData();
 int left = encoders.getLeftCount();
 int right = encoders.getRightCount();
 Serial.print("Left rotations: ");
 Serial.println(left/12);
 Serial.print("Right rotations: ");
 Serial.println(right/12);
 delay(1000); // Wacht een seconde voordat je opnieuw meet
}