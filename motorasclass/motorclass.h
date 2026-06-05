#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

class motorclass {
  public:
    motorclass();
    void moveforwardZumo();
    void movebackwardZumo();
    void turnleftZumo();
    void turnrightZumo();
    void turnssharpleftZumo();
    void turnsshaprightZumo();
    void stopZumo();
    void speedfastZumo();
    void speedslowZumo();
    void setSpeed(int16_t newSpeed);
    void turnleftbackwardZumo();
    void turnrightbackwardZumo();
    int16_t getSpeed() const;
    ~motorclass();
  private:
    Zumo32U4Motors motors;
    int16_t speed;
};