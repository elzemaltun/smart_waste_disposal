#include <Arduino.h>
#include "Scheduler.h"
#include "ContainerManagementTask.h"
#include "Debug.h"
#include "MsgService.h"

extern MsgServiceClass MsgService;

bool isFull = false;  // Example: Waste bin status
float temperature = 25.0;  // Example: Initial temperature
int wasteLevel = 50;  // Example: Initial waste level percentage
void msgCheck();

// Scheduler and Task
Scheduler sched;
ContainerManagementTask* containerTask;

void setup() {
    // Initialize debug output
    Debugger.begin(9600);
    Debugger.println("Container Management System Initializing...");

    // Initialize scheduler
    sched.init(50);  // 50ms base period

    // Create ContainerManagementTask
    // containerTask = new ContainerManagementTask();
    // containerTask->init(100);  // 100ms task period
    // sched.addTask(containerTask);

    MsgService.init();

    Debugger.println("System Setup Complete.");
}

void loop() {
    // sched.schedule();
    msgCheck();
}

// msgCheck function to handle message processing and status updates
void msgCheck() {
    // Check for incoming messages
    if (MsgService.isMsgAvailable()) {
      Msg* msg = MsgService.receiveMsg();
      String command = msg->getContent();
      Debugger.println("Command received");
    
      // Handle commands
      if (command == "EMPTY") {
        isFull = false;
        MsgService.sendMsg("WASTE_EMPTIED");
        Debugger.println("Waste bin emptied");
      } else if (command == "FIXED") {
        MsgService.sendMsg("SYSTEM_FIXED");
      }

    // Debugging: Print the command received
    Debugger.println("Command received: " + command);
  }

    // Send periodic status updates
    // String status = "IS_FULL:" + String(isFull) + ", TEMPERATURE:" + String(temperature) + ", WASTE_LEVEL:" + String(wasteLevel);
    // MsgService.sendMsg(status);
}