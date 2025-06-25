#pragma once
#include <Arduino.h>

namespace LCD {

/**
 * @brief Initialize the LCD display.
 * 
 * Sets up the display, clears the screen, and homes the cursor.
 * Prints an error to Serial if initialization fails.
 */
void init();

/**
 * @brief Clear the display and reset the cursor.
 * 
 * Clears all content and homes the cursor to the top left.
 */
void clear();

/**
 * @brief Print a message at the next available line and auto-advance.
 * 
 * @param message Null-terminated string to print.
 */
void print(const char* message);

/**
 * @brief Print a message at a specific line (column 0).
 * 
 * @param message Null-terminated string to print.
 * @param line Line number (0-3).
 */
void printAt(const char* message, byte line);

/**
 * @brief Print a message at a specific line and column.
 * 
 * @param message Null-terminated string to print.
 * @param line Line number (0-3).
 * @param col Column number (0-19).
 */
void printAt(const char* message, byte line, byte col);

/**
 * @brief Print a multi-line message, splitting on '\n'.
 * 
 * Each line is printed on a separate LCD row. Remaining lines are cleared.
 * @param message Null-terminated string with optional newline characters.
 */
void printMultiLine(const char* message);

/**
 * @brief Print a long message across all 4 lines with word wrapping.
 * 
 * Wraps words to new lines, and force-breaks long words if needed.
 * @param message Null-terminated string to display.
 */
void printWrapped(const char* message);

/**
 * @brief Toggle the display backlight on or off.
 */
void toggleBacklight();

}
