#include "ServoController.h"
#include <Arduino.h>

ServoController::ServoController(int pin) {
    this->pin = pin;
}

void ServoController::init() {
    servo.attach(pin);
    Serial.println("Servo initialized");
    closeDoor(); // Start with door closed
}

void ServoController::openDoor(int angle) {
    Serial.println("Opening door...");
    servo.write(angle); // Open door
}

void ServoController::closeDoor() {
    Serial.println("Closing door...");
    servo.write(0); // Close door
}

void ServoController::emptyContainer(int angle) {
    Serial.println("Emptying container...");
    servo.write(angle); // Move door in reverse direction
}
