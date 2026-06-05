#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "motorclass.h"


motorclass::motorclass() : motors() {
  int speed = 200;
}
void motorclass::moveZumo() {
  motors.setSpeeds(speed, speed);
}
void motorclass::stopZumo() {
  motors.setSpeeds(0, 0);
}
void motorclass::movebackwardZumo() {
  motors.setSpeeds(-speed, -speed);
}
void motorclass::turnleftZumo() {
  motors.setSpeeds(0, speed);
}
void motorclass::turnrightZumo() {
  motors.setSpeeds(speed, 0);
}
void motorclass::turnssharpleftZumo() {
  motors.setSpeeds(-speed, speed);
}
void motorclass::turnsshaprightZumo() {
  motors.setSpeeds(speed, -speed);
}
void motorclass::speedfastZumo() {
  speed = 400;
}
void motorclass::speedslowZumo() {
  speed = 200;
}
motorclass::~motorclass() {
  motors.setSpeeds(0, 0);
}
