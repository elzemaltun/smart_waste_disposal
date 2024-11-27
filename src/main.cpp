#include <Arduino.h>
#include "Button.h"
#include "ServoController.h"
#include "blink_led_task.h"
#include "scheduler.h"
#include "pir_sensor.h"
#include "sonar_sensor.h"

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

void pirSensorCheck(void);
void sonarSensorCheck(void);

void setup() {
  Serial.begin(9600);
  /* sched.init(50);
  blinkTask = new BlinkTask(13, 12); // Red LED on pin 13, Green LED on pin 12
  blinkTask->init(100); // Period set to 100ms 
  sched.addTask(blinkTask); */
}

void loop() {
  // Example: Update states based on sensor data
/*   if (errorDetected) {
    blinkTask->setState(BlinkTask::RED_ON);
  } else if (userDetected) {
    blinkTask->setState(BlinkTask::GREEN_ON);
  } else {
    blinkTask->setState(BlinkTask::OFF);
  }
  sched.schedule();
 */

  sonarSensorCheck(); 
  pirSensorCheck(); 
  
}

void sonarSensorCheck() {
  SonarSensor sonarSensor;
  sonarSensor.init(2, 3);
  Serial.println(sonarSensor.checkWasteLevel(2, 3));
  //Serial.println(sonarSensor.getDistance(2, 3));
}

void pirSensorCheck() {
  PirSensor pirSensor;
  pirSensor.init(7);
  Serial.println(pirSensor.isMotionDetected(7)); 
}