#include "display.h"

// Use your desired constructor arguments here (I2C address 0x27, 20 columns, 4 rows)
LCDDisplay lcd(0x27, 20, 4);

LCDDisplay::LCDDisplay(uint8_t i2c_addr, uint8_t cols, uint8_t rows)
     : lcd(i2c_addr, cols, rows), cols(cols), rows(rows), cursorLine(0), backlightOn(true) {
}

void LCDDisplay::init() {
     if (lcd.begin(cols, rows) != hd44780::RV_ENOERR) {
          Serial.println("Display initialization failed!");
          return;
     }
     lcd.clear();
     lcd.home();
     cursorLine = 0;
}

void LCDDisplay::clear() {
     lcd.clear();
     lcd.home();
     cursorLine = 0;
}

void LCDDisplay::print(const char* message) {
     lcd.setCursor(0, cursorLine);
     char buf[21];
     snprintf(buf, sizeof(buf), "%-20s", message);
     lcd.print(buf);
     cursorLine = (cursorLine + 1) % rows;
}

void LCDDisplay::printAt(const char* message, uint8_t line) {
     lcd.setCursor(0, line);
     char buf[21];
     snprintf(buf, sizeof(buf), "%-20s", message);
     lcd.print(buf);
}

void LCDDisplay::printAt(const char* message, uint8_t line, uint8_t col) {
     lcd.setCursor(col, line);
     char buf[21];
     int len = strlen(message);
     if (col == 0) {
          snprintf(buf, sizeof(buf), "%-20s", message);
     }
     else {
          int available = 20 - col;
          snprintf(buf, sizeof(buf), "%-*.*s", available, available, message);
     }
     lcd.print(buf);
}

void LCDDisplay::printMultiLine(const char* message) {
     int line = 0;
     const char* ptr = message;
     const char* lineStart = ptr;

     while (*ptr && line < rows) {
          if (*ptr == '\n' || *(ptr + 1) == '\0') {
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

     while (line < rows) {
          lcd.setCursor(0, line++);
          lcd.print("                    ");
     }
     cursorLine = 0;
}

void LCDDisplay::toggleBacklight() {
     if (backlightOn) {
          lcd.noBacklight();
     }
     else {
          lcd.backlight();
     }

     backlightOn = !backlightOn;
}

void LCDDisplay::printWrapped(const char* message) {
     lcd.clear();
     cursorLine = 0;

     const int maxLineLength = 20;
     char lineBuf[21] = { 0 };
     int bufIndex = 0;

     const char* wordStart = message;
     const char* ptr = message;

     while (*ptr && cursorLine < rows) {
          if (*ptr == ' ' || *(ptr + 1) == '\0') {
               bool isLastChar = (*(ptr + 1) == '\0');
               int wordLen = ptr - wordStart + (isLastChar ? 1 : 0);
               int spaceNeeded = (bufIndex > 0 ? 1 : 0) + wordLen;

               if (spaceNeeded + bufIndex > maxLineLength) {
                    lineBuf[bufIndex] = '\0';
                    lcd.setCursor(0, cursorLine++);
                    lcd.print(lineBuf);
                    if (cursorLine >= rows) break;

                    strncpy(lineBuf, wordStart, wordLen);
                    bufIndex = wordLen;
               }
               else {
                    if (bufIndex > 0) lineBuf[bufIndex++] = ' ';
                    strncpy(&lineBuf[bufIndex], wordStart, wordLen);
                    bufIndex += wordLen;
               }

               wordStart = ptr + 1;
          }

          if ((ptr - wordStart + 1) >= maxLineLength) {
               strncpy(lineBuf, wordStart, maxLineLength);
               lineBuf[maxLineLength] = '\0';
               lcd.setCursor(0, cursorLine++);
               lcd.print(lineBuf);
               if (cursorLine >= rows) break;

               wordStart = ptr + 1;
               bufIndex = 0;
          }

          ptr++;
     }

     if (cursorLine < rows && bufIndex > 0) {
          lineBuf[bufIndex] = '\0';
          lcd.setCursor(0, cursorLine++);
          lcd.print(lineBuf);
     }

     while (cursorLine < rows) {
          lcd.setCursor(0, cursorLine++);
          lcd.print("                    ");
     }

     cursorLine = 0;
}
