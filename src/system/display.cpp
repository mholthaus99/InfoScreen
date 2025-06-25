#include "display.h"
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

namespace LCD
{

    hd44780_I2Cexp lcd(0x27, 20, 4); // I2C address 0x27, 20x4 display
    static int cursorLine = 0;

    void init()
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

    void clear()
    {
        lcd.clear();
        lcd.home();
        cursorLine = 0;
    }

    void print(const char *message)
    {
        lcd.setCursor(0, cursorLine);

        char buf[21];
        snprintf(buf, sizeof(buf), "%-20s", message);
        lcd.print(buf);

        cursorLine = (cursorLine + 1) % 4;
    }

    void printAt(const char *message, byte line)
    {
        lcd.setCursor(0, line);

        char buf[21];
        snprintf(buf, sizeof(buf), "%-20s", message);
        lcd.print(buf);
    }

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

        while (line < 4)
        {
            lcd.setCursor(0, line++);
            lcd.print("                    ");
        }

        cursorLine = 0;
    }

    void toggleBacklight()
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
            if (*ptr == ' ' || *(ptr + 1) == '\0')
            {
                bool isLastChar = (*(ptr + 1) == '\0');
                int wordLen = ptr - wordStart + (isLastChar ? 1 : 0);
                int spaceNeeded = (bufIndex > 0 ? 1 : 0) + wordLen;

                if (spaceNeeded + bufIndex > maxLineLength)
                {
                    lineBuf[bufIndex] = '\0';
                    lcd.setCursor(0, cursorLine++);
                    lcd.print(lineBuf);
                    if (cursorLine >= 4)
                        break;

                    strncpy(lineBuf, wordStart, wordLen);
                    bufIndex = wordLen;
                }
                else
                {
                    if (bufIndex > 0)
                        lineBuf[bufIndex++] = ' ';
                    strncpy(&lineBuf[bufIndex], wordStart, wordLen);
                    bufIndex += wordLen;
                }

                wordStart = ptr + 1;
            }

            if ((ptr - wordStart + 1) >= maxLineLength)
            {
                strncpy(lineBuf, wordStart, maxLineLength);
                lineBuf[maxLineLength] = '\0';
                lcd.setCursor(0, cursorLine++);
                lcd.print(lineBuf);
                if (cursorLine >= 4)
                    break;

                wordStart = ptr + 1;
                bufIndex = 0;
            }

            ptr++;
        }

        if (cursorLine < 4 && bufIndex > 0)
        {
            lineBuf[bufIndex] = '\0';
            lcd.setCursor(0, cursorLine++);
            lcd.print(lineBuf);
        }

        while (cursorLine < 4)
        {
            lcd.setCursor(0, cursorLine++);
            lcd.print("                    ");
        }

        cursorLine = 0;
    }

} // namespace LCD
