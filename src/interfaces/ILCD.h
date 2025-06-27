#pragma once
#include <stdint.h>

class ILCD {
public:
     virtual void begin() = 0;
     virtual void clear() = 0;
     virtual void setCursor(uint8_t col, uint8_t row) = 0;
     virtual void print(const char* str) = 0;
     virtual void print(char ch) = 0;
     virtual void backlight(bool enable) = 0;
     virtual void toggleBacklight() = 0;
     virtual uint8_t getCols() const = 0;
     virtual uint8_t getRows() const = 0;
     virtual ~ILCD() {}
};
