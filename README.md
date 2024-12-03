# Smart Waste Disposal Container

## Overview

This project implements an embedded system called **Smart Waste Disposal Container**, designed for disposing of dangerous liquid waste in a safe and efficient manner. It features an Arduino-based subsystem communicating with a PC-based GUI application (Operator Dashboard) to monitor and manage the container's state.

---

## Features

### Basic Functionality
- Users can dispose of liquid waste by opening a servo-controlled door.
- The system tracks waste levels and becomes unavailable when full.
- Operators can empty and restore the container using the GUI dashboard.

### Detailed Behavior
1. **Startup State:**
   - The container is empty and available.
   - Green LED (L1) signals availability.
   - Servo motor is set to 0° (door closed).
   - LCD displays: `PRESS OPEN TO ENTER WASTE`.

2. **Waste Entry Process:**
   - User presses the `OPEN` button to open the door (servo rotates to +90°).
   - LCD displays: `PRESS CLOSE WHEN DONE`.
   - Door closes automatically after a timeout or when the `CLOSE` button is pressed.
   - LCD displays: `WASTE RECEIVED` for a brief period before returning to idle state.

3. **Full Container State:**
   - Detected by sonar when waste level exceeds a threshold.
   - LCD displays: `CONTAINER FULL`.
   - L1 (green LED) turns off; L2 (red LED) turns on.
   - Door automatically closes if the container becomes full during waste entry.

4. **Operator Interaction:**
   - The Operator Dashboard allows monitoring and managing the container:
     - **"Empty" Button:** Opens the door to -90° for emptying, then closes it.
     - **"Restore" Button:** Resets the container after alarms.
   - Displays waste level percentage and temperature.

5. **Temperature Monitoring:**
   - TEMP sensor monitors internal temperature.
   - If temperature exceeds a threshold for too long, the container becomes unavailable:
     - LCD displays: `PROBLEM DETECTED`.
     - L1 turns off; L2 turns on.
     - Operators must restore the container using the dashboard.

---

## Hardware Components

| Component         | Description                                                                 |
|-------------------|-----------------------------------------------------------------------------|
| **USER DETECTOR** | PIR sensor to detect user presence.                                         |
| **WASTE DETECTOR**| Sonar sensor to measure waste level.                                        |
| **DOOR**          | Servo motor controlling the waste entry door.                              |
| **USER LCD**      | I2C LCD to display messages to users.                                      |
| **OPEN/CLOSE**    | Tactile buttons to control door operations.                                |
| **L1 (Green LED)**| Indicates system availability.                                             |
| **L2 (Red LED)**  | Indicates system unavailability or alarms.                                 |
| **TEMP**          | Analog temperature sensor for monitoring container temperature.            |

---

## Software Design

### Arduino Subsystem
- **Task-Based Architecture:** Implements tasks for user detection, waste monitoring, door control, and temperature sensing.
- **Finite State Machines (FSMs):**
  - Manages system states: Startup, Accepting Waste, Full, and Alarm.

### Operator Dashboard
- **Features:**
  - Displays waste level percentage and temperature.
  - Provides buttons for emptying and restoring the container.
  - Logs optional history of events.

---

## How to Run

### Arduino Setup
1. Upload the Arduino sketch to the microcontroller.
2. Connect the hardware components as per the schematic.

### Operator Dashboard
1. Compile and run the GUI application on a PC.
2. Connect the Arduino to the PC via serial.

### Demonstration Steps
1. Turn on the system and observe the startup state.
2. Simulate user actions: open, close, and enter waste.
3. Fill the container (block the sınar sensor) and test the full state behavior.
4. Use the GUI to empty and restore the container. (unavailable at the moment)
5. Trigger a temperature alarm and restore the system. (unavailable at the moment)

---

## Current Issues
- **GUI Functionality:** The GUI is currently symbolic as the messaging system does not work.
- **Arduino Communication:** Arduino is unable to send messages to the GUI.

### Requirements
- Use the `pyserial` library for Python to establish communication between Arduino and the GUI.
  ```bash
  pip install pyserial
  ```
---

## Future Improvements
- Fix the messaging system to enable end-to-end communication between the Arduino and GUI.
- Add history logging for waste disposal and alarms.

