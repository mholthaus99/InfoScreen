#pragma once
#include <stdint.h>

class ILCD {
public:
     virtual void begin(uint8_t cols, uint8_t rows) = 0;
     virtual void clear() = 0;
     virtual void setCursor(uint8_t col, uint8_t row) = 0;
     virtual void print(const char* str) = 0;
     virtual void print(char ch) = 0;
     virtual void backlight(bool enable) = 0;
     virtual void toggleBacklight() = 0;
     virtual ~ILCD() {}
};
