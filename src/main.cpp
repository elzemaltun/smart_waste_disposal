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
      //
      break;
    case SLEEP_MODE:
      //
      break;
    case USER_DETECTED:
      //
      break;
    case IS_OPENING:
      //
      break;
    case IS_CLOSING:
      //
      break;
    case IS_FULL:
      //
      break;
    case IS_EMPTYING:
      //
      break;
    case ERROR_STATE:
      //
      break;
  };
}

