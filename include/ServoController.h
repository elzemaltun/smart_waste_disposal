#ifndef __SERVOCONTROLLER__
#define __SERVOCONTROLLER__

#include <ServoTimer2.h>  // Include ServoTimer2 library

class ServoController {
public:
    ServoController(int pin);
    void init();                   // Initialize servo
    void openDoor(int angle = 90); // Opens door for waste
    void closeDoor();              // Closes door
    void emptyContainer(int angle = -90); // Reverse open for emptying

private:
    int pin;
    ServoTimer2 servo;  // Use ServoTimer2 to control the servo
};

#endif
