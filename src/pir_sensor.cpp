#include "pir_sensor.h"
#include "Arduino.h"

void PirSensor::init(int pin) {
    this->pin = pin;
    motionDetected = false;
    pinMode(pin, INPUT);
}

bool PirSensor::isMotionDetected(int pin) {
    bool current = digitalRead(pin);
    if (current != motionDetected ){
        motionDetected = current;
    }
    return motionDetected;
}