#include "blink_led_task.h"
#include <Arduino.h>

BlinkTask::BlinkTask(int pin_red, int pin_green){
  this->pin_red = pin_red;
  this->pin_green = pin_green;      
}
  
void BlinkTask::init(int period){
  Task::init(period);
  led_red = new Led(pin_red); 
  led_green = new Led(pin_green);
  // state = OFF;    
}
  
void BlinkTask::tick(){

  Debugger.print("this is a tick");
  switch (state) {
    case OFF: // Both LEDs are off
    Debugger.print("please work");
      led_red->switchOff();
      led_green->switchOff();
      break;

    case RED_ON: // Red LED on, Green LED off
      Debugger.print("this is red state");
      led_red->switchOn();
      led_green->switchOff();
      break;

    case GREEN_ON: // Green LED on, Red LED off
      Debugger.print("this is green state");
      led_red->switchOff();
      led_green->switchOn();
      break;
  }
}

void BlinkTask::setState(State newState) {
  this->state = newState; // Update the state
}
