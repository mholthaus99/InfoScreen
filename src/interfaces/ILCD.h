#pragma once
#include <stdint.h>

/**
 * @brief Interface for LCD display operations.
 *
 * This abstract class defines the interface for controlling an LCD display.
 * Implementations must provide methods for initialization, clearing the display,
 * setting the cursor position, printing characters or strings, and controlling
 * the backlight. It also provides methods to query the display's dimensions.
 */
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
