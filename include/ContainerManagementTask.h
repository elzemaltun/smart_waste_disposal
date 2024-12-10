#ifndef CONTAINER_MANAGEMENT_TASK_H
#define CONTAINER_MANAGEMENT_TASK_H

#include <Arduino.h>
#include <avr/sleep.h>
#include "Task.h"
#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "TemperatureMonitor.h"
#include "PirSensor.h"
#include "SonarSensor.h"
#include "Led.h"

class ContainerManagementTask : public Task {
public:
    ContainerManagementTask();

    enum State {
        IDLE,
        SLEEP,
        READY,
        DOOR_OPEN,
        DOOR_CLOSE,
        FULL,
        EMPTY_CONTAINER,
        OVER_TEMP
    };


    void init(int period) override;
    void tick() override;

    // Add these public methods
    State getCurrentState();
    float getCurrentTemperature();
    int getDoorState();
    void setState(State newState); // Make this public

    // check to see if the container is full public beacuse used in gui task
    bool isContainerFull();
    float getWasteLevel(); 
    
    // Pin Configurations
    #define SONAR_TRIG_PIN 4  
    #define SONAR_ECHO_PIN 5  

    // Configuration constants
    #define SLEEP_TIMEOUT               10000   // 10 seconds before going to sleep
    #define DOOR_OPEN_TIMEOUT           5000    // 5 seconds door open timeout
    #define WASTE_DISPLAY_TIME          2000    // Display "WASTE RECEIVED" time
    #define EMPTY_CONTAINER_TIME        3000    // Time to empty container
    #define MAX_TEMP                    50.0    // Maximum temperature threshold
    #define WASTE_LEVEL_THRESHOLD       0.3     // Waste level threshold (from sonar implementation)

    // Test simulation definition
    #define TEST_EMPTY_CONTAINER_TIMELIMIT  10000 // wait for 10 seconds before emptying the container | no gui test
    #define TEST_OVER_TEMP_TIMELIMIT        10000 // wait for 10 seconds before going to ready | no gui test
    #define CHECK_TEMP_TIMELIMIT            5000 // wait for 10 seconds before going to sleep | no gui test
    
private:
    

    // Component instances
    Button* doorOpenButton;
    Button* doorCloseButton;
    LcdController* display;
    ServoController* containerDoor;
    TemperatureMonitor* tempSense;
    PirSensor* motionSense;
    SonarSensor* wasteLevelSensor;
    Led* alarmLed;
    Led* availableLed;

    // Current state and timing
    State currentState;
    unsigned long lastStateChangeTime;

    // State change method
    //void setState(State newState);

    // Helper methods -> made public because they are used in guimessageservicetask
    //bool isContainerFull();

    void enterSleepMode();
};

#endif // CONTAINER_MANAGEMENT_TASK_H
