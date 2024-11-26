#include <Arduino.h>
#include "Button.h"
#include "ServoController.h"
#include "blink_led_task.h"
#include "scheduler.h"

// --- Pin Definitions ---
#define OPEN_BUTTON_PIN 6
#define CLOSE_BUTTON_PIN 7
#define SERVO_PIN 9
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

// --- Objects ---
Button openButton(OPEN_BUTTON_PIN);
Button closeButton(CLOSE_BUTTON_PIN);
ServoController servoController(SERVO_PIN);

Scheduler sched;
BlinkTask* blinkTask;

// --- States ---
bool errorDetected = false;
bool userDetected = true;

void setup() {
    // Serial Initialization
    Serial.begin(9600);

    // --- Waste Door Control Initialization ---
    openButton.init();
    closeButton.init();
    servoController.init();

    // --- LED Blink and Scheduler Initialization ---
    sched.init(50);
    blinkTask = new BlinkTask(RED_LED_PIN, GREEN_LED_PIN);
    blinkTask->init(100); // Period set to 100ms
    sched.addTask(blinkTask);
}

void loop() {
    // --- Waste Door Control Section ---
    if (openButton.isPressed()) {
        servoController.openDoor();
        Serial.println("Door opened for waste.");
    }

    if (closeButton.isPressed()) {
        servoController.closeDoor();
        Serial.println("Door closed after waste.");
    }

    // Uncomment for servo operation testing
    /*
    servoController.openDoor();
    Serial.println("Door opened for waste.");
    delay(1000);
    servoController.closeDoor();
    Serial.println("Door closed after waste.");
    delay(1000);
    servoController.emptyContainer();
    Serial.println("Container emptied.");
    delay(1000);
    servoController.closeDoor();
    Serial.println("Container emptied.");
    delay(1000);
    */

    // --- LED Blink and Scheduler Section ---
    if (errorDetected) {
        blinkTask->setState(BlinkTask::RED_ON);
        Serial.println("This is RED state if statement");
    } else if (userDetected) {
        blinkTask->setState(BlinkTask::GREEN_ON);
        Serial.println("This is GREEN state if statement");
    } else {
        blinkTask->setState(BlinkTask::OFF);
        Serial.println("This is OFF state if statement");
    }

    sched.schedule();
}