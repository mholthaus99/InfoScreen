#pragma once

#include <Arduino.h>
#include "Wire.h"
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>



class LCDDisplay {
public:
    LCDDisplay(uint8_t i2c_addr = 0x27, uint8_t cols = 20, uint8_t rows = 4);

    void init();
    void clear();
    void print(const char* message);
    void printAt(const char* message, uint8_t line);
    void printAt(const char* message, uint8_t line, uint8_t col);
    void printMultiLine(const char* message);
    void printWrapped(const char* message);
    void toggleBacklight();

private:
    hd44780_I2Cexp lcd;
    uint8_t cols;
    uint8_t rows;
    uint8_t cursorLine;
    bool backlightOn;
};
