#include "pir_sensor.h"
#include "Arduino.h"

void PirSensor::init(int pin) {
    this->pin = pin;
    motionDetected = false;
    pinMode(pin, INPUT);
}

void PirSensor::enableInterrupt() {
    // Accessing the class member pin directly (no need to pass pin as an argument)
    attachInterrupt(digitalPinToInterrupt(this->pin), NULL, RISING);  // Enable interrupt on motion detection
}

void PirSensor::disableInterrupt() {
    // Accessing the class member pin directly
    detachInterrupt(digitalPinToInterrupt(this->pin));  // Disable interrupt
}


bool PirSensor::isMotionDetected(int pin) {
    bool current = digitalRead(pin);
    if (current != motionDetected ){
        motionDetected = current;
    }
    return motionDetected;
}