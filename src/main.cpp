#include <Arduino.h>
#include "LcdController.h"
#include "Button.h"
#include "ServoController.h"
#include "TemperatureMonitor.h"
#include "blink_led_task.h"
#include "scheduler.h"
#include "pir_sensor.h"
#include "sonar_sensor.h"

// --- Pin Definitions ---
#define OPEN_BUTTON_PIN 6
#define CLOSE_BUTTON_PIN 7
#define SERVO_PIN 9
#define TEMP_SENSOR_PIN A0
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

// --- LCD Configuration ---
LcdController lcd(0x27, 16, 2);

// --- Button, Servo, and Temperature Monitor ---
Button openButton(OPEN_BUTTON_PIN);
Button closeButton(CLOSE_BUTTON_PIN);
ServoController servoController(SERVO_PIN);
TemperatureMonitor tempMonitor(TEMP_SENSOR_PIN);

// --- Scheduler and Blink Task ---
Scheduler sched;
BlinkTask* blinkTask;

// --- PIR and Sonar Sensors ---
PirSensor pirSensor;
SonarSensor sonarSensor;

// --- States ---
int lcdTestState = 0;
int servoTestState = 0;
bool errorDetected = false;
bool userDetected = true;

// --- Timing Variables ---
unsigned long lastLCDUpdateTime = 0;
unsigned long lastTempCheckTime = 0;
unsigned long lastServoActionTime = 0;

// --- Intervals ---
const unsigned long lcdUpdateInterval = 3000;  // 3 seconds
const unsigned long tempCheckInterval = 1000;  // 1 second
const unsigned long servoActionInterval = 1000; // 1 second

// --- Function Declarations ---
void initializeLCD();
void testLCDSequence();
void handleButtonActions();
void testServoSequence();
void checkTemperature();
void pirSensorCheck();
void sonarSensorCheck();

void setup() {
    Serial.begin(9600);

    // Initialize LCD
    lcd.init();
    initializeLCD();

    // Initialize buttons, servo, and temperature monitor
    openButton.init();
    closeButton.init();
    servoController.init();
    Serial.println("Temperature Monitor Initialized");

    // Initialize PIR and Sonar Sensors
    pirSensor.init(7);    // PIR Sensor on pin 7
    sonarSensor.init(2, 3); // Sonar Sensor on pins 2 (Trig) and 3 (Echo)

    // Initialize Scheduler and Blink Task
    sched.init(50);
    blinkTask = new BlinkTask(RED_LED_PIN, GREEN_LED_PIN);
    blinkTask->init(100); // Blink task period set to 100ms
    sched.addTask(blinkTask);

    Serial.println("System Initialized");
}

void loop() {
    testLCDSequence();    // Test LCD sequence
    checkTemperature();   // Test temperature monitoring
    handleButtonActions(); // Handle button-based servo operations
    testServoSequence();  // Test servo sequence
    pirSensorCheck();     // Check PIR sensor for motion detection
    sonarSensorCheck();   // Check Sonar sensor for waste level
    sched.schedule();     // Scheduler for LED blink task
}

/**
 * Initializes the LCD to display the first message.
 */
void initializeLCD() {
    lcd.displayPressOpen();
    Serial.println("LCD Initialized with 'Press Open' message.");
}

/**
 * Tests the LCD sequence in a non-blocking manner.
 */
void testLCDSequence() {
    unsigned long currentTime = millis();

    if (currentTime - lastLCDUpdateTime >= lcdUpdateInterval) {
        lastLCDUpdateTime = currentTime;

        switch (lcdTestState) {
        case 0:
            Serial.println("Displaying: Press Open to Enter Waste");
            lcd.displayPressOpen();
            break;
        case 1:
            Serial.println("Displaying: Press Close When Done");
            lcd.displayPressClose();
            break;
        case 2:
            Serial.println("Displaying: Waste Received");
            lcd.displayWasteReceived();
            break;
        case 3:
            Serial.println("Displaying: Container Full");
            lcd.displayContainerFull();
            break;
        case 4:
            Serial.println("Displaying: Problem Detected");
            lcd.displayProblemDetected();
            break;
        case 5:
            Serial.println("Turning LCD Off");
            lcd.lcdPowerOff();
            break;
        default:
            Serial.println("Restarting LCD Test Sequence...");
            lcdTestState = -1;
            break;
        }

        lcdTestState++;
    }
}

/**
 * Monitors the temperature and checks if it exceeds the threshold.
 */
void checkTemperature() {
    unsigned long currentTime = millis();

    if (currentTime - lastTempCheckTime >= tempCheckInterval) {
        lastTempCheckTime = currentTime;

        float temperatureC = tempMonitor.readTemperatureC();
        bool thresholdExceeded = tempMonitor.isThresholdExceeded();

        Serial.print("Temperature: ");
        Serial.print(temperatureC);
        Serial.println(" °C");

        if (thresholdExceeded) {
            Serial.println("WARNING: Temperature threshold exceeded!");
            errorDetected = true;
        } else {
            Serial.println("Temperature is within the safe range.");
            errorDetected = false;
        }
    }
}

/**
 * Handles button press actions for controlling the servo.
 */
void handleButtonActions() {
    if (openButton.isPressed()) {
        servoController.openDoor();
        Serial.println("Door opened for waste.");
    }

    if (closeButton.isPressed()) {
        servoController.closeDoor();
        Serial.println("Door closed after waste.");
    }
}

/**
 * Tests the servo operations in a non-blocking sequence.
 */
void testServoSequence() {
    unsigned long currentTime = millis();

    if (currentTime - lastServoActionTime >= servoActionInterval) {
        lastServoActionTime = currentTime;

        switch (servoTestState) {
        case 0:
            servoController.openDoor();
            Serial.println("Servo Test: Door opened.");
            break;
        case 1:
            servoController.closeDoor();
            Serial.println("Servo Test: Door closed.");
            break;
        case 2:
            servoController.emptyContainer();
            Serial.println("Servo Test: Container emptied.");
            break;
        case 3:
            servoController.closeDoor();
            Serial.println("Servo Test: Container re-closed.");
            break;
        default:
            Serial.println("Servo Test Sequence Complete. Restarting...");
            servoTestState = -1;
            break;
        }

        servoTestState++;
    }
}

/**
 * Checks the PIR sensor for motion detection.
 */
void pirSensorCheck() {
    if (pirSensor.isMotionDetected(7)) {
        Serial.println("PIR Sensor: Motion Detected!");
        userDetected = true;
    } else {
        Serial.println("PIR Sensor: No Motion Detected.");
        userDetected = false;
    }
}

/**
 * Checks the Sonar sensor for waste level.
 */
void sonarSensorCheck() {
    float distance = sonarSensor.getDistance(2, 3);
    Serial.print("Sonar Sensor: Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 10.0) { // Example threshold
        Serial.println("Sonar Sensor: Waste level high!");
        errorDetected = true;
    } else {
        Serial.println("Sonar Sensor: Waste level okay.");
        errorDetected = false;
    }
}
