#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Debug.h"

class LcdController {
private:
    LiquidCrystal_I2C lcd;
    uint8_t lcdCols;
    uint8_t lcdRows;

public:
    LcdController(uint8_t address, uint8_t cols, uint8_t rows);
    void init();
    void displayPressOpen();
    void displayPressClose();
    void displayWasteReceived();
    void displayContainerFull();
    void displayProblemDetected();
    void lcdPowerOff();
    void lcdPowerOn();
};

#endif // LCDCONTROLLER_H
