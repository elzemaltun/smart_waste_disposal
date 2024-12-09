#include "ServoController.h"
#include <Arduino.h>

int doorStatus = 0; // global definition

ServoController::ServoController(int pin) {
    this->pin = pin;
}

void ServoController::init() {
    servo.attach(pin);
    Debugger.println("Servo initialized");
    closeDoor(); // Start with door closed
}

void ServoController::openDoor(int angle) {
    Debugger.println("Opening door...");
    servo.write(angle); // Open door
    doorStatus = 1;
}

void ServoController::closeDoor(int angle) {
    Debugger.println("Closing door...");
    servo.write(angle); // Close door
    doorStatus = 0;
}

void ServoController::emptyContainer(int angle) {
    Debugger.println("Emptying container...");
    servo.write(angle); // Move door in reverse direction
    doorStatus = 2;
}

