#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

class ZumoScanner
{
private:
  Zumo32U4ProximitySensors proxSensors;
  uint8_t links;
  uint8_t rechts;

public:
  ZumoScanner() : links(0), rechts(0) {}

  void begin()
  {
    proxSensors.initThreeSensors();
  }

  void update()
  {
    proxSensors.read();
    links = proxSensors.countsFrontWithLeftLeds();
    rechts = proxSensors.countsFrontWithRightLeds();
  }

  void printData()
  {
    Serial.print("L: ");
    Serial.print(links);
    Serial.print(" | R: ");
    Serial.println(rechts);
  }
};

ZumoScanner scanner;

void setup()
{
  Serial.begin(9600);
  scanner.begin();
}

void loop()
{
  scanner.update();

  scanner.printData();

  delay(100);
}