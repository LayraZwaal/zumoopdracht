#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

class motorclass {
  public:
    motorclass();
    void moveZumo();
    void stopZumo();
    ~motorclass();
  private:
    Zumo32U4Motors motors;
};