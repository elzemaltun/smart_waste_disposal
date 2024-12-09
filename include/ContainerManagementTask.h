#ifndef CONTAINER_MANAGEMENT_TASK_H
#define CONTAINER_MANAGEMENT_TASK_H

#include <Arduino.h>
#include <avr/sleep.h>
#include "Task.h"
#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "TemperatureMonitor.h"
#include "pir_sensor.h"
#include "sonar_sensor.h"
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
    
    
private:
    // Pin Configurations
    static constexpr int SONAR_TRIG_PIN = 4;  // Example pin, adjust as needed
    static constexpr int SONAR_ECHO_PIN = 5;  // Example pin, adjust as needed

    // Configuration constants
    static constexpr unsigned long SLEEP_TIMEOUT = 10000;       // 10 seconds before going to sleep
    static constexpr unsigned long DOOR_OPEN_TIMEOUT = 5000;    // 5 seconds door open timeout
    static constexpr unsigned long WASTE_DISPLAY_TIME = 2000;   // Display "WASTE RECEIVED" time
    static constexpr unsigned long EMPTY_CONTAINER_TIME = 3000; // Time to empty container
    static constexpr float MAX_TEMP = 50.0;                     // Maximum temperature threshold
    static constexpr float WASTE_LEVEL_THRESHOLD = 0.3;         // Waste level threshold (from sonar implementation)

    // Test simulation definition
    #define TEST_EMPTY_CONTAINER_TIMELIMIT  10000 // wait for 10 seconds before emptying the container | no gui test
    #define TEST_OVER_TEMP_TIMELIMIT        10000 // wait for 10 seconds before going to ready | no gui test

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
