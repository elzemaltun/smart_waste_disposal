#include "ContainerManagementTask.h"
#include "Debug.h"

ContainerManagementTask::ContainerManagementTask() {
    currentState = IDLE;
    lastStateChangeTime = millis();
}

void ContainerManagementTask::init(int period) {
    Task::init(period);

    // Initialize component instances
    doorOpenButton = new Button(6);  // Open button pin
    doorCloseButton = new Button(7);  // Close button pin
    display = new LcdController(0x27, 16, 2);
    containerDoor = new ServoController(9);  // Servo pin
    tempSense = new TemperatureMonitor(A0);  // Temperature sensor pin
    motionSense = new PirSensor();
    wasteLevelSensor = new SonarSensor();
    alarmLed = new Led(11);  // Red LED pin
    availableLed = new Led(10);  // Green LED pin

    // Initialize all components
    doorOpenButton->init();
    doorCloseButton->init();
    motionSense->init(2);  // PIR sensor pin
    wasteLevelSensor->init(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
    containerDoor->init();
    display->init();

    // Set initial state
    setState(IDLE);

    Debugger.println("Container Management Task Initialized");
}

bool ContainerManagementTask::isContainerFull() {
    return wasteLevelSensor->checkWasteLevel(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
}

void ContainerManagementTask::setState(State newState) {
    // One-time actions when entering a new state
    switch (newState) {
        case IDLE:
            availableLed->switchOn();   // L1 ON
            alarmLed->switchOff();      // L2 OFF
            display->displayPressOpen();
            Debugger.println("Entered IDLE state");
            break;

        case SLEEP:
            availableLed->switchOn();  // Keep L1 ON
            Debugger.println("Entered SLEEP state");
            break;

        case READY:
            availableLed->switchOn();   // L1 ON
            alarmLed->switchOff();      // L2 OFF
            display->displayPressOpen();
            Debugger.println("Entered READY state");
            break;

        case DOOR_OPEN:
            containerDoor->openDoor();  // Rotate motor to +90°
            display->displayPressClose();
            Debugger.println("Entered DOOR_OPEN state");
            break;

        case DOOR_CLOSE:
            containerDoor->closeDoor();  // Rotate motor to 0°
            display->displayWasteReceived();
            Debugger.println("Entered DOOR_CLOSE state");
            break;

        case FULL:
            availableLed->switchOff();  // L1 OFF
            alarmLed->switchOn();       // L2 ON
            containerDoor->closeDoor();
            display->displayContainerFull();
            Debugger.println("Entered FULL state");
            break;

        case EMPTY_CONTAINER:
            containerDoor->emptyContainer();  // Rotate motor to -90°
            availableLed->switchOn();   // L1 ON
            alarmLed->switchOff();      // L2 OFF
            display->displayPressOpen();
            Debugger.println("Entered EMPTY_CONTAINER state");
            break;

        case OVER_TEMP:
            availableLed->switchOff();  // L1 OFF
            alarmLed->switchOn();       // L2 ON
            containerDoor->closeDoor();
            display->displayProblemDetected();
            Debugger.println("Entered OVER_TEMP state");
            break;
    }

    // Update state and timestamp
    currentState = newState;
    lastStateChangeTime = millis();
}

 float currentTemp; // global definition    

void ContainerManagementTask::tick() {
    // Check for temperature first (highest priority)
    currentTemp = tempSense->readTemperatureC();
    
    // Temperature override
    if (currentTemp > MAX_TEMP) {
        setState(OVER_TEMP);
        return;
    }

    // State machine logic
    switch (currentState) {
        case IDLE:
            // Check for user approach via PIR
            if (motionSense->isMotionDetected(2)) {
                setState(READY);
                return;
            }
            // Check for sleep timeout
            else if (millis() - lastStateChangeTime > SLEEP_TIMEOUT) {
                setState(SLEEP);
                return;
            }
            break;

        case SLEEP:
            // Periodically check for motion
            // ENABLE INTERRUPT LATER!!!!
            if (motionSense->isMotionDetected(2)) {
                setState(READY);
                return;
            }
            break;

        case READY:
            // Check for open button press
            if (doorOpenButton->isPressed()) {
                setState(DOOR_OPEN);
                return;
            }
            break;

        case DOOR_OPEN:
            // Check for close button or timeout
            if (doorCloseButton->isPressed() || 
                (millis() - lastStateChangeTime > DOOR_OPEN_TIMEOUT)) {
                setState(DOOR_CLOSE);
                return;
            }
            
            // Check waste level
            if (isContainerFull()) {
                setState(FULL);
                return;
            }
            break;

        case DOOR_CLOSE:
            // Check waste level
            if (isContainerFull()) {
                setState(FULL);
                return;
            }

            // Transition back to READY after display time
            if (millis() - lastStateChangeTime > WASTE_DISPLAY_TIME) {
                setState(READY);
                return;
            }
            break;

        case FULL:
            // Wait for GUI "EMPTY" command (simulated here with a placeholder)
            // In a real system, this would be replaced with an actual GUI command
            setState(EMPTY_CONTAINER);
            return;

        case EMPTY_CONTAINER:
            // Check if emptying is complete
            if (millis() - lastStateChangeTime > EMPTY_CONTAINER_TIME) {
                setState(READY);
                return;
            }
            break;

        case OVER_TEMP:
            // Wait for GUI "RESTORE" command (simulated here with a placeholder)
            // In a real system, this would be replaced with an actual GUI command
            setState(READY);
            return;
    }
}