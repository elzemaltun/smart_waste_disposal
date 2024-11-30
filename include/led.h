#ifndef __LED__
#define __LED__

#include "light.h"
#include "Debug.h"

class Led: public Light { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();    
private:
  int pin;  
};

#endif
