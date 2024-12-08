#ifndef GUI_MESSAGE_SERVICE_TASK_H
#define GUI_MESSAGE_SERVICE_TASK_H

#include <Arduino.h>
#include <Queue.h> // Custom Queue class for managing messages
#include "Task.h"
#include "ContainerManagementTask.h"

class GuiMessageServiceTask : public Task {
public:
    GuiMessageServiceTask(ContainerManagementTask* containerTask);
    void init(int period) override;
    void tick() override;
    void readSerial(); // Continuously reads serial input and buffers messages

private:
    // Reference to ContainerManagementTask
    ContainerManagementTask* containerTask;

    // Parsing state
    enum ParseState { WAIT, PROCESS, SEND_STATUS };
    ParseState currentParseState;

    // Variables for parsing
    bool emptyCommand;
    bool restoreCommand;
    int statusCode;

    // Message queue for buffering serial data
    Queue<String> messageQueue;
    String incomingMessageBuffer;

    // Helper methods
    void processIncomingMessage(const String& message);
    void sendStatus();
    void resetParseState();
};

#endif // GUI_MESSAGE_SERVICE_TASK_H
