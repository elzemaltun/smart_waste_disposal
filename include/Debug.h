#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

// Enable or disable debugging globally
#define DEBUG_ENABLED true // Set to false to disable debug output

class Debug {
public:
    static void begin(long baudRate) {
#if DEBUG_ENABLED
        Serial.begin(baudRate);
#endif
    }

    template <typename T>
    static void print(T value) {
#if DEBUG_ENABLED
        Serial.print(value);
#endif
    }

    template <typename T>
    static void println(T value) {
#if DEBUG_ENABLED
        Serial.println(value);
#endif
    }

    static void print(const char* message) {
#if DEBUG_ENABLED
        Serial.print(message);
#endif
    }

    static void println(const char* message) {
#if DEBUG_ENABLED
        Serial.println(message);
#endif
    }
};

// Static instance of Debug class (this is optional, only needed if you want instance-based access)
extern Debug Debugger;

#endif
