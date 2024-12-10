#ifndef __SERVOCONTROLLER__
#define __SERVOCONTROLLER__

#include "ServoTimer2.h"  
#include "Debug.h"

class ServoController {
public:
    ServoController(int pin);
    void init();                            // Initialize servo
    void openDoor(int angle = 1000);        // Opens door for waste
    void closeDoor(int angle = 1500);       // Closes door
    void emptyContainer(int angle = 2000);  // Reverse open for emptying

private:
    int pin;
    ServoTimer2 servo;  
};

#endif
