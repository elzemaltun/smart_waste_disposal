#include <Arduino.h>

enum state{
  INITIAL_STATE,
  SLEEP_MODE,
  USER_DETECTED,
  IS_OPENING,
  IS_CLOSING,
  IS_FULL,  
  IS_EMPTYING,
  ERROR_STATE
};

state current_state = INITIAL_STATE;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  switch(current_state) {
    case INITIAL_STATE:
      // if no user detected durin Tsleep, enter SLEEP_MODE
      // if user detected, enter USER_DETECTED mode
      break;
    case SLEEP_MODE:
      // if user detected, enter INITIAL_STATE
      break;
    case USER_DETECTED:
      // led L1 is on
      // lcd displays PRESS OPEN TO ENTER WASTE
      // if button B1 is pressed, enter IS_OPENING mode
      // if no button is pressed time Tsleep, enter SLEEP_MODE 
      break;
    case IS_OPENING:
      // Rotate servo motor +90 degrees
      // lcd displays PRESS CLOSE WHEN DONE
      // if button B2 is pressed, or time T1 has passed or if waste_level < D1, enter IS_CLOSING
      break;
    case IS_CLOSING:
      // Rotate servo motor 0 degrees
      // WASTE RECEIVED
      // if T2 seconds passed, check for waste level
      // if waste_level < D1 enter IS_FULL
      // else enter INITIAL_STATE 
      break;
    case IS_FULL:
      // lcd displays CONTAINER FULL
      // led L2 is on, L1 is off
      // if empty_the_container message received, enter IS_EMPTYING
      break;
    case IS_EMPTYING:
      // rotate motor -90 degrees
      // if T3 time has passed, rotate motor 0 degrees
      // if waste_level > D1, enter INITIAL_STATE
      break;
    case ERROR_STATE:
      // Turn on led L2, turn off led L1
      // lcd displays PROBLEM DETECTED
      break;
  };
}

