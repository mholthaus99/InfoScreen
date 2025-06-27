#pragma once
#include "interfaces/ILCD.h"
#include <Arduino.h>
#include "Wire.h"
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

class Hd44780Adapter : public ILCD {
public:
     Hd44780Adapter(hd44780_I2Cexp& lcd) : _lcd(lcd) {}

     void begin(uint8_t cols, uint8_t rows) override {
          _lcd.begin(0x27, cols, rows);
     }

     void clear() override {
          _lcd.clear();
     }

     void setCursor(uint8_t col, uint8_t row) override {
          _lcd.setCursor(col, row);
     }

     void print(const char* str) override {
          _lcd.print(str);
     }

     void print(char ch) override {
          _lcd.print(ch);
     }

     void backlight(bool enable) override {
          if (enable) _lcd.backlight();
          else _lcd.noBacklight();
     }

     void toggleBacklight() override{
          if(backlightIsOn){
               _lcd.noBacklight();
               backlightIsOn = false;
          } else {
               _lcd.backlight();
               backlightIsOn = true;
          }
     }

private:
     hd44780_I2Cexp& _lcd;
     bool backlightIsOn;
};
