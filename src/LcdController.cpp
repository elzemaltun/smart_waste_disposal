#include "LcdController.h"

LcdController::LcdController(uint8_t address, uint8_t cols, uint8_t rows)
    : lcd(address, cols, rows), lcdCols(cols), lcdRows(rows) {}

void LcdController::init() {
    lcd.init();
    lcd.begin(lcdCols, lcdRows); // Correctly specify dimensions
    lcd.backlight();
}

void LcdController::displayPressOpen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Open");
    lcd.setCursor(0, 1);
    lcd.print("to enter waste");
}

void LcdController::displayPressClose() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Close");
    lcd.setCursor(0, 1);
    lcd.print("when done");
}

void LcdController::displayWasteReceived() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waste received");
    lcd.setCursor(0, 1);
    lcd.print("Thank you!");
}

void LcdController::displayContainerFull() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Container Full");
    lcd.setCursor(0, 1);
    lcd.print("Please empty it");
}

void LcdController::displayProblemDetected() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Problem Detected");
    lcd.setCursor(0, 1);
    lcd.print("Check system");
}

void LcdController::lcdPowerOff() {
    lcd.clear();
    lcd.noBacklight(); // Turn off the backlight
}

void LcdController::lcdPowerOn() {
    lcd.backlight();
}
