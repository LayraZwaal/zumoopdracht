#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "motorclass.h"

 motorclass motors;

void setup() {
  Serial.begin(9600);
  // Initialiseer de motoren en encoders
 
}

void loop() {
  // Update de encoderwaarden
motors.moveforwardZumo();
delay(1000);
motors.movebackwardZumo();
delay(1000);
motors.turnleftZumo();
delay(1000);
motors.turnrightZumo();
delay(1000);
motors.turnssharpleftZumo();
delay(1000);
motors.turnsshaprightZumo();
delay(1000);
motors.turnleftbackwardZumo();
delay(1000);
motors.turnrightbackwardZumo();
delay(1000);
motors.stopZumo();
}  