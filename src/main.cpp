#include <Arduino.h>
#include "Scheduler.h"
#include "ContainerManagementTask.h"
#include "GuiMessageServiceTask.h"
#include "Debug.h"

// Scheduler and Tasks
Scheduler sched;
ContainerManagementTask* containerTask;
GuiMessageServiceTask* guiMessageTask;

void setup() {
    // Initialize debug output
    Debugger.begin(9600);
    Debugger.println("Container Management System Initializing...");

    // Initialize scheduler
    sched.init(50);  // 50ms base period

    // Create and initialize ContainerManagementTask
    containerTask = new ContainerManagementTask();
    containerTask->init(100);  // 100ms task period
    sched.addTask(containerTask);

    // Create and initialize GuiMessageServiceTask
    guiMessageTask = new GuiMessageServiceTask(containerTask);
    guiMessageTask->init(100);  // 100ms task period
    sched.addTask(guiMessageTask);

    Debugger.println("System Setup Complete.");
}

void loop() {
    guiMessageTask->readSerial(); // Always read serial data
    sched.schedule();
}
