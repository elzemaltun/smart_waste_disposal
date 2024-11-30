#include "TemperatureMonitor.h"

// Constructor
TemperatureMonitor::TemperatureMonitor(uint8_t analogPin, float refVoltage) {
    pin = analogPin;
    voltageRef = refVoltage;
    thresholdExceeded = false; // Initialize the threshold flag
}

// Internal method to update the thresholdExceeded flag
void TemperatureMonitor::updateThresholdStatus(float temperature) {
    thresholdExceeded = (temperature > THRESHOLD_C);
}

// Read temperature in Celsius and check against the threshold
float TemperatureMonitor::readTemperatureC() {
    int raw = analogRead(pin); // Read raw ADC value
    float voltage = (raw * voltageRef) / 1023.0; // Convert ADC value to voltage
    float temperatureC = (voltage - 0.5) * 100.0; // TMP36 conversion formula

    // Update the threshold status
    updateThresholdStatus(temperatureC);

    return temperatureC;
}

// Check if the threshold is exceeded
bool TemperatureMonitor::isThresholdExceeded() {
    return thresholdExceeded;
}
