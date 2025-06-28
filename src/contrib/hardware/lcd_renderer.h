#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "../../interfaces/IViewRenderer.h"

/**
 * @brief Renderer for HD44780 LCD displays using I2C.
 * This class provides methods to render text on an HD44780 LCD display
 * connected via I2C, supporting multiple rows and columns.
 */
class Hd44780LcdRenderer : public IViewRenderer {
   public:
    /**
     * @brief Constructs the Hd44780LcdRenderer with the specified I2C address, columns, and rows.
     * @param i2cAddress The I2C address of the LCD.
     * @param cols The number of columns on the LCD.
     * @param rows The number of rows on the LCD.
     */
    Hd44780LcdRenderer();
    // Hd44780LcdRenderer(uint8_t i2cAddress, uint8_t cols, uint8_t rows);

    // /**
    //  * @brief Calls the lcd instance .begin() method to initialize the display.
    //  * This method should be called before using the display.
    //  * TODO: see if I can remove this method and just call _lcd.begin() directly in the
    //  constructor.
    //  */
    // void begin();

    /**
     * @brief Draws text at a specific column and row on the LCD.
     * @param col The column to start drawing at (0-indexed).
     * @param row The row to start drawing at (0-indexed).
     * @param text The text to draw.
     */
    void drawText(uint8_t col, uint8_t row, const char* text) override;

    /**
     * @brief Draws text at a specific row on the LCD.
     * @param row The row to start drawing at (0-indexed).
     * @param text The text to draw.
     */
    void drawText(uint8_t row, const char* text) override;

    /**
     * @brief Draws text on the LCD, maintaining a rolling buffer of strings.
     * This method will scroll the display if the text exceeds the available space.
     * @param text The text to draw.
     */
    void drawText(const char* text) override;

    /**
     * @brief Draws wrapped text on the LCD.
     * @param text The text to draw, which may contain spaces for wrapping.
     */
    void drawWrap(const char* text) override;

    /**
     * @brief Clears the LCD display.
     * This method will clear all text from the display.
     */
    void clear() override;

    /**
     * @brief Toggles the backlight of the LCD display.
     * This method will turn the backlight on if it is currently off, and vice versa.
     */
    void toggleBacklight();

   private:
    /**
     * @brief The HD44780 I2C display instance.
     * This instance is used to interact with the LCD display.
     */
    hd44780_I2Cexp _lcd;

    /**
     * @brief The I2C address of the LCD display.
     * This address is used to communicate with the LCD over I2C.
     */
    uint8_t _i2cAddress;

    /**
     * @brief The number of columns on the LCD display.
     * This is used to determine how much space is available for text.
     */
    uint8_t _cols;

    /**
     * @brief The number of rows on the LCD display.
     * This is used to determine how many lines of text can be displayed.
     */
    uint8_t _rows;

    /**
     * @brief The current row being written to on the LCD.
     * This is used to keep track of where to write the next line of text.
     */
    uint8_t _currentRow;

    /**
     * @brief Indicates whether the backlight is currently on.
     * This is used to toggle the backlight state.
     */
    bool _backlightOn;
};
