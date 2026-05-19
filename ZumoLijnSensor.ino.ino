#include "LineSensorManager.h"

LineSensorManager sensorManager;

void setup() {
    Serial.begin(9600);
    sensorManager.init();
    sensorManager.calibrate();
}

void loop() {
    sensorManager.debugToSerial();
    delay(100);
}