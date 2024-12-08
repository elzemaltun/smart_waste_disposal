#include <Arduino.h>
#include "Scheduler.h"
#include "ContainerManagementTask.h"
#include "Debug.h"
#include "MsgService.h"

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
    containerTask = new ContainerManagementTask();
    containerTask->init(100);  // 100ms task period
    sched.addTask(containerTask);

    Debugger.println("System Setup Complete.");
}

void loop() {
    sched.schedule();
    // MsgService.sendMsg("this is arduino debug 1");
    // if (MsgService.isMsgAvailable()) {
    //     Msg* msg = MsgService.receiveMsg();    
    //     if (msg->getContent() == "this is python"){
    //         delay(500);
    //         MsgService.sendMsgStr("this is arduino debug 2");
    //     }        
    //     delete msg;
    //}
}