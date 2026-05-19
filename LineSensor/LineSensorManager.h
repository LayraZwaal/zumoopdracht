#ifndef LINESENSORMANAGER_H
#define LINESENSORMANAGER_H

#include <Zumo32U4.h>

 * @class LineSensorManager
 * @brief Klasse voor het beheren van de 5 Zumo lijnsensoren.
 */
class LineSensorManager {
  private:
    Zumo32U4LineSensors _lineSensors;
    Zumo32U4OLED _display;
    uint16_t _sensorValues[5];

  public:
    // Constructor
    LineSensorManager();

    // Publieke methoden
    void init();
    void calibrate();
    int16_t getPosition();
    void debugToSerial();
    uint16_t* getRawValues();
};

#endif