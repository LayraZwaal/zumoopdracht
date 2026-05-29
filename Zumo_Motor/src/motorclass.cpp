#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>


motorclass::motorclass() {
Zumo32U4Motors motors;
}
void motorclass::moveZumo() {
  //setSpeeds zet de snelheid van de motors 400 is het snelst vooruit, -400 het snelst achteruit.
  //Delay zegt hoelang in miliseconden hij door gaat.
  motors.setSpeeds(200, 200);
}
void motorclass::stopZumo() {
  motors.setSpeeds(0, 0);
}
motorclass::~motorclass() {
  motors.setSpeeds(0, 0);
}