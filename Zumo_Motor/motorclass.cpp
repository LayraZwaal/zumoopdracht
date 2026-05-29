#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "motorclass.h"


motorclass::motorclass() : motors() {
}
void motorclass::moveZumo() {
  motors.setSpeeds(200, 200);
}
void motorclass::stopZumo() {
  motors.setSpeeds(0, 0);
}
motorclass::~motorclass() {
  motors.setSpeeds(0, 0);
}