#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "../interfaces/IViewRenderer.h"

class Hd44780LcdRenderer : public IViewRenderer {
public:
    Hd44780LcdRenderer(uint8_t i2cAddress, uint8_t cols, uint8_t rows);

    void begin();
  

     void drawText(uint8_t col, uint8_t row, const char* text) override;
     void drawText(uint8_t row, const char* text) override;
     void drawText(const char* text) override;
   
    void drawWrap(const char* text) override;
    void clear() override;
    void toggleBacklight();

private:
    hd44780_I2Cexp _lcd;
    uint8_t _i2cAddress;
    uint8_t _cols;
    uint8_t _rows;
  
    uint8_t _currentRow;
    bool _backlightOn;

  
};
