#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"
#include "Debug.h"

class BlinkTask: public Task {

  int pin_green;
  int pin_red;
  Light* led_green;
  Light* led_red;
  

public:
  enum State{OFF, RED_ON, GREEN_ON};
  BlinkTask(int pin_red, int pin_green); 
  void init(int period);  
  void tick();
  void setState(State newState);

private:
  State state;
};

#endif

