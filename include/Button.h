#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

class Button {
public:
    Button(int pin, unsigned long debounceDelay = 50);
    void init();
    bool isPressed();

private:
    int pin;
    bool lastState;
    bool currentState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
};

#endif