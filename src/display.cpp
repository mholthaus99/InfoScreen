#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "display.h"

/// @brief LCD display object for 20x4 I2C display at address 0x27
hd44780_I2Cexp lcd(0x27, 20, 4);

/// @brief Tracks the next available line for print()
static int cursorLine = 0;

/**
 * @brief Initialize the LCD display.
 * 
 * Sets up the display, clears the screen, and homes the cursor.
 * Prints an error to Serial if initialization fails.
 */
void lcd_init()
{
    if (lcd.begin(20, 4) != hd44780::RV_ENOERR)
    {
        Serial.println("Display initialization failed!");
        return;
    }
    lcd.clear();
    lcd.home();
    cursorLine = 0;
}

/**
 * @brief Clear the display and reset the cursor.
 * 
 * Clears all content and homes the cursor to the top left.
 */
void lcd_clear()
{
    lcd.clear();
    lcd.home();
    cursorLine = 0;
}

/**
 * @brief Print a message at the current cursor line and advance to the next line.
 * 
 * @param message Null-terminated string to print.
 * 
 * Prints the message left-aligned and wraps to the top after the last line.
 */
void print(const char *message)
{
    // Print message at the current cursorLine
    lcd.setCursor(0, cursorLine);

    char buf[21];
    snprintf(buf, sizeof(buf), "%-20s", message);
    lcd.print(buf);

    // Advance line, wrap to top if necessary
    cursorLine = (cursorLine + 1) % 4;
}

/**
 * @brief Print a message at a specific line (column 0).
 * 
 * @param message Null-terminated string to print.
 * @param line Line number (0-3).
 */
void printAt(const char *message, byte line)
{
    lcd.setCursor(0, line);

    char buf[21];
    snprintf(buf, sizeof(buf), "%-20s", message);
    lcd.print(buf);
}

/**
 * @brief Print a message at a specific line and column.
 * 
 * @param message Null-terminated string to print.
 * @param line Line number (0-3).
 * @param col Column number (0-19).
 */
void printAt(const char *message, byte line, byte col)
{
    lcd.setCursor(col, line);

    char buf[21];
    int len = strlen(message);

    if (col == 0)
    {
        snprintf(buf, sizeof(buf), "%-20s", message);
    }
    else
    {
        int available = 20 - col;
        snprintf(buf, sizeof(buf), "%-*.*s", available, available, message);
    }

    lcd.print(buf);
}

/**
 * @brief Print a multi-line message, splitting on '\n'.
 * 
 * @param message Null-terminated string with optional newline characters.
 * 
 * Each line is printed on a separate LCD row. Remaining lines are cleared.
 */
void printMultiLine(const char *message)
{
    int line = 0;
    const char *ptr = message;
    const char *lineStart = ptr;

    while (*ptr && line < 4)
    {
        if (*ptr == '\n' || *(ptr + 1) == '\0')
        {
            char buf[21];
            int len = ptr - lineStart + (*(ptr + 1) == '\0' ? 1 : 0);
            strncpy(buf, lineStart, len);
            buf[len] = '\0';

            lcd.setCursor(0, line);
            lcd.print("                    ");
            lcd.setCursor(0, line);
            lcd.print(buf);

            lineStart = ptr + 1;
            line++;
        }
        ptr++;
    }

    // Clear any remaining lines
    while (line < 4)
    {
        lcd.setCursor(0, line);
        lcd.print("                    ");
        line++;
    }

    cursorLine = 0; // Reset tracked line after full redraw
}

/**
 * @brief Toggle the display backlight on or off.
 * 
 * Remembers the current state and toggles it each call.
 */
void lcd_toggleBacklight()
{
    static bool isOn = true;
    if (isOn)
    {
        lcd.noBacklight();
    }
    else
    {
        lcd.backlight();
    }
    isOn = !isOn;
}


/**
 * @brief Print a long message across all 4 lines of the display, word-wrapping intelligently.
 * 
 * Words will wrap to the next line when reaching the edge of the display.
 * If a word is longer than 20 characters, it will be force-split.
 * 
 * @param message Null-terminated string to display.
 */
void printWrapped(const char *message)
{
    lcd.clear();
    cursorLine = 0;

    const int maxLineLength = 20;
    char lineBuf[21] = {0};
    int bufIndex = 0;

    const char *wordStart = message;
    const char *ptr = message;

    while (*ptr && cursorLine < 4)
    {
        if (*ptr == ' ' || *(ptr + 1) == '\0')  // Word boundary or end of message
        {
            bool isLastChar = (*(ptr + 1) == '\0');
            int wordLen = ptr - wordStart + (isLastChar ? 1 : 0);
            int spaceNeeded = (bufIndex > 0 ? 1 : 0) + wordLen;

            if (spaceNeeded + bufIndex > maxLineLength)
            {
                // Print the current buffer to LCD
                lineBuf[bufIndex] = '\0';
                lcd.setCursor(0, cursorLine++);
                lcd.print(lineBuf);

                if (cursorLine >= 4) break;

                // Start new line with the word (no leading space)
                strncpy(lineBuf, wordStart, wordLen);
                bufIndex = wordLen;
            }
            else
            {
                // Add a space if not at beginning of line
                if (bufIndex > 0)
                    lineBuf[bufIndex++] = ' ';

                strncpy(&lineBuf[bufIndex], wordStart, wordLen);
                bufIndex += wordLen;
            }

            wordStart = ptr + 1;
        }

        // Force-break a word that is longer than one line
        if ((ptr - wordStart + 1) >= maxLineLength)
        {
            strncpy(lineBuf, wordStart, maxLineLength);
            lineBuf[maxLineLength] = '\0';
            lcd.setCursor(0, cursorLine++);
            lcd.print(lineBuf);

            if (cursorLine >= 4) break;

            wordStart = ptr + 1;
            bufIndex = 0;
        }

        ptr++;
    }

    // Print any remaining text in buffer
    if (cursorLine < 4 && bufIndex > 0)
    {
        lineBuf[bufIndex] = '\0';
        lcd.setCursor(0, cursorLine++);
        lcd.print(lineBuf);
    }

    // Clear leftover lines
    while (cursorLine < 4)
    {
        lcd.setCursor(0, cursorLine++);
        lcd.print("                    ");
    }

    cursorLine = 0;
}
