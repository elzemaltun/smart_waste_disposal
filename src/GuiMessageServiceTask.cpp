#include "GuiMessageServiceTask.h"
#include "Debug.h"

//extern int statusCode;
 int statusCode;

GuiMessageServiceTask::GuiMessageServiceTask(ContainerManagementTask* containerTask) {
    this->containerTask = containerTask;
    this->currentParseState = WAIT;
    this->emptyCommand = false;
    this->restoreCommand = false;
    //this->statusCode = 0;
}

void GuiMessageServiceTask::init(int period) {
    Task::init(period);
    Serial.begin(9600); // Initialize serial communication
    Debugger.println("GUI Message Service Initialized");
}

void GuiMessageServiceTask::tick() {
    readSerial();    
    if (!messageQueue.isEmpty()) {               
        
        Debugger.println("Processing message from queue");
        String incomingMessage = messageQueue.dequeue(); // Retrieve the oldest message
        processIncomingMessage(incomingMessage);

        if (emptyCommand) {
        
            Debugger.println("EMPTY CMD received");
            if (containerTask->getCurrentState() == ContainerManagementTask::FULL)
                containerTask->setState(ContainerManagementTask::EMPTY_CONTAINER);
            /* if (containerTask->isContainerFull()) {
                containerTask->setState(ContainerManagementTask::EMPTY_CONTAINER);
                statusCode = 0; // No error
            } else {
                statusCode = 1; // FULL error
            } */
        }
        if (restoreCommand) {
            Debugger.println("RESTORE CMD received");
            if (containerTask->getCurrentState() == ContainerManagementTask::OVER_TEMP) 
                containerTask->setState(ContainerManagementTask::READY);
            /* if (containerTask->getCurrentState() == ContainerManagementTask::OVER_TEMP) {
            containerTask->setState(ContainerManagementTask::READY);
            statusCode = 0; // No error
            } else {
            statusCode = 2; // Overheating error
            } */
        }
        sendStatus();
        resetParseState();
    }
}

void GuiMessageServiceTask::processIncomingMessage(const String& message) {
    // Validate message format
    if (message.startsWith("{REQ,") && message.endsWith("}")) {
        // Remove curly braces
        String content = message.substring(5, message.length() - 1); // Extract "EMPTY,RESTORE"
        int firstComma = content.indexOf(',');

        if (firstComma != -1) {
            // Extract EMPTY and RESTORE values
            String emptyStr = content.substring(0, firstComma);
            String restoreStr = content.substring(firstComma + 1);

            // Validate and parse EMPTY command
            if (emptyStr.equals("1") || emptyStr.equals("0")) {
                emptyCommand = emptyStr.toInt();
            } else {
                Debugger.println("Invalid EMPTY value");
                return; // Abort parsing
            }

            // Validate and parse RESTORE command
            if (restoreStr.equals("1") || restoreStr.equals("0")) {
                restoreCommand = restoreStr.toInt();
            } else {
                Debugger.println("Invalid RESTORE value");
                return; // Abort parsing
            }

            Debugger.println("Message parsed successfully");
        } else {
            Debugger.println("Invalid message format: missing comma");
        }
    } else {
        Debugger.println("Invalid message format");
    }
}

void GuiMessageServiceTask::sendStatus() {
    // Calculate status values
    float wasteLevel = containerTask->getWasteLevel(); // Store distance as float
    float temperature = containerTask->getCurrentTemperature();
    int doorState = containerTask->getDoorState(); // 0: Closed, 1: Open, 2: Empty

    // Format and send response
    String response = String("{ACK,") +
                      String(wasteLevel) + "," +
                      String(temperature, 1) + "," + // Send temperature with 1 decimal place
                      String(doorState) + "," +
                      String(statusCode) + "}";
    Serial.println(response);
}

void GuiMessageServiceTask::resetParseState() {
    emptyCommand = false;
    restoreCommand = false;
    //statusCode = 0;
}

// Continuous serial reading and buffering
void GuiMessageServiceTask::readSerial() {
    while (Serial.available()) {
        char ch = Serial.read();
        if (ch == '\n') { // End of a message
            if (incomingMessageBuffer.length() > 0) {
                messageQueue.enqueue(incomingMessageBuffer);
                incomingMessageBuffer = "";
            }
        } else {
            incomingMessageBuffer += ch;
        }
    }
}
