#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "./interfaces/IViewRenderer.h"

class Hd44780LcdRenderer : public IViewRenderer {
public:
    Hd44780LcdRenderer(uint8_t i2cAddress, uint8_t cols, uint8_t rows)
        : _i2cAddress(i2cAddress), _cols(cols), _rows(rows),
        _col(0), _row(0), _backlightOn(true) {
    }

    void begin() {
        _lcd.begin(_cols, _rows, _i2cAddress);
        _lcd.backlight();
    }

    void drawText(int col, int row, const char* text) override {
        Serial.printf("Drawing text at col: %d, row: %d, text: %s\n", col, row, text);
        _lcd.setCursor(col, row);
        _lcd.print(text);
        _col = col;
        _row = row;
    }

    void drawTextonLine(int row, const char* text) override {
        _lcd.setCursor(0, row);
        char buf[21];
        snprintf(buf, sizeof(buf), "%-20s", text);
        _lcd.print(buf);
        Serial.println(buf);
    }

    void drawWrap(const char* text) override {
        for (const char* p = text; *p; ++p) {
            if (*p == '\n') {
                newline();
            }
            else {
                if (_col >= _cols) newline();
                _lcd.setCursor(_col, _row);
                _lcd.print(*p);
                _col++;
            }
        }
    }

    void clear() override {
        _lcd.clear();
        _col = 0;
        _row = 0;
    }

    void toggleBacklight() {
        if (_backlightOn) {
            _lcd.noBacklight();
        }
        else {
            _lcd.backlight();
        }
        _backlightOn = !_backlightOn;
    }

private:
    hd44780_I2Cexp _lcd;
    uint8_t _i2cAddress;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _col;
    uint8_t _row;
    bool _backlightOn;

    void newline() {
        _col = 0;
        _row = (_row + 1) % _rows;
        _lcd.setCursor(_col, _row);
    }
};
