#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include <Arduino.h>
#include "Debug.h"

class TemperatureMonitor {
private:
    uint8_t pin;           // Analog pin for the temperature sensor
    float voltageRef;      // Reference voltage for the ADC
    const float THRESHOLD_C = 30.0; // Threshold temperature in Celsius
    bool thresholdExceeded; // Flag to indicate if the threshold is exceeded

    // Internal method to update the thresholdExceeded flag
    void updateThresholdStatus(float temperature);

public:
    // Constructor
    TemperatureMonitor(uint8_t analogPin, float refVoltage = 5.0);

    // Method to read temperature in Celsius
    float readTemperatureC();

    // Method to check if the threshold is exceeded
    bool isThresholdExceeded();
};

#endif 