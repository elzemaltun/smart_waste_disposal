#include <Arduino.h>
#include "blink_led_task.h"
#include "scheduler.h"

Scheduler sched;
BlinkTask* blinkTask;

bool errorDetected = false;
bool userDetected = true;

void setup() {
  Serial.begin(9600);
  sched.init(50);
  blinkTask = new BlinkTask(13, 12); // Red LED on pin 13, Green LED on pin 12
  blinkTask->init(100); // Period set to 100ms 
  sched.addTask(blinkTask);
}

void loop() {
  // Example: Update states based on sensor data
  if (errorDetected) {
    blinkTask->setState(BlinkTask::RED_ON);
    Serial.print("this is red state if statement");
  } else if (userDetected) {
    blinkTask->setState(BlinkTask::GREEN_ON);
    Serial.print("this is green state if statement");
  } else {
    blinkTask->setState(BlinkTask::OFF);
    Serial.print("this is off state if statement");
  }

  sched.schedule();
}


