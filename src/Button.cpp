#include "Button.h"

Button::Button(int pin, unsigned long debounceDelay) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    lastState = LOW;
    currentState = LOW;
    lastDebounceTime = 0;
}

void Button::init() {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    bool reading = digitalRead(pin);

    if (reading == LOW) {
        return true;
    } else {
        return false;
    }
}

/* bool Button::isPressed() {
    bool reading = digitalRead(pin);

    if (reading != lastState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != currentState) {
            currentState = reading;
            if (currentState == LOW) { // Button pressed
                lastState = reading;
                return true;
            }
        }
    }

    lastState = reading;
    return false;
}
 */