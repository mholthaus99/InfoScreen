#include "lcd_renderer.h"

Hd44780LcdRenderer::Hd44780LcdRenderer(uint8_t i2cAddress, uint8_t cols, uint8_t rows)
    : _lcd(),
      _i2cAddress(i2cAddress),
      _cols(cols),
      _rows(rows),
      _currentRow(0),
      _backlightOn(true) {
    // Initialize the LCD with the specified I2C address and dimensions
}

void Hd44780LcdRenderer::begin() {
    Wire.begin();
    _lcd.begin(_cols, _rows, _i2cAddress);
    _lcd.backlight();
}

void Hd44780LcdRenderer::drawText(uint8_t col, uint8_t row, const char* text) {
    _lcd.setCursor(col, row);
    char buf[_cols + 1];
    int len = strlen(text);
    if (col == 0) {
        snprintf(buf, sizeof(buf), "%-20s", text);
    } else {
        int available = 20 - col;
        snprintf(buf, sizeof(buf), "%-*.*s", available, available, text);
    }
    _lcd.print(buf);
}

void Hd44780LcdRenderer::drawText(uint8_t row, const char* text) {
    //_lcd.clear();
    _lcd.setCursor(0, row);
    char buf[_cols + 1];
    snprintf(buf, sizeof(buf), "%-20s", text);
    _lcd.print(buf);
    Serial.println(buf);
}
void Hd44780LcdRenderer::drawText(const char* text) {
    // Maintain a rolling buffer of strings
    static std::vector<String> lineBuffer(_rows, String("                    "));  // 20 spaces

    // Format the new line to fit 20 chars
    char buf[21];
    snprintf(buf, sizeof(buf), "%-20s", text);  // Left-align and pad to 20 characters
    String newLine(buf);

    // Scroll the buffer up by removing the top line and adding the new one at the end
    lineBuffer.erase(lineBuffer.begin());
    lineBuffer.push_back(newLine);

    // Redraw the whole display
    for (uint8_t row = 0; row < _rows; row++) {
        _lcd.setCursor(0, row);
        _lcd.print(lineBuffer[row]);
    }

    // Also print to Serial for debug
    Serial.println(newLine);
}

void Hd44780LcdRenderer::clear() {
    _lcd.clear();
    _currentRow = 0;
}

void Hd44780LcdRenderer::toggleBacklight() {
    if (_backlightOn) {
        _lcd.noBacklight();
    } else {
        _lcd.backlight();
    }
    _backlightOn = !_backlightOn;
}

void Hd44780LcdRenderer::drawWrap(const char* text) {
    _lcd.clear();
    _currentRow = 0;

    const int maxLineLength = _cols;
    char lineBuf[_cols + 1] = {0};
    int bufIndex = 0;

    const char* wordStart = text;
    const char* ptr = text;

    while (*ptr && _currentRow < _rows) {
        if (*ptr == ' ' || *(ptr + 1) == '\0') {
            bool isLastChar = (*(ptr + 1) == '\0');
            int wordLen = ptr - wordStart + (isLastChar ? 1 : 0);
            int spaceNeeded = (bufIndex > 0 ? 1 : 0) + wordLen;

            if (spaceNeeded + bufIndex > maxLineLength) {
                lineBuf[bufIndex] = '\0';
                _lcd.setCursor(0, _currentRow++);
                _lcd.print(lineBuf);
                if (_currentRow >= _rows) break;

                strncpy(lineBuf, wordStart, wordLen);
                bufIndex = wordLen;
            } else {
                if (bufIndex > 0) lineBuf[bufIndex++] = ' ';
                strncpy(&lineBuf[bufIndex], wordStart, wordLen);
                bufIndex += wordLen;
            }

            wordStart = ptr + 1;
        }

        if ((ptr - wordStart + 1) >= maxLineLength) {
            strncpy(lineBuf, wordStart, maxLineLength);
            lineBuf[maxLineLength] = '\0';
            _lcd.setCursor(0, _currentRow++);
            _lcd.print(lineBuf);
            if (_currentRow >= _rows) break;

            wordStart = ptr + 1;
            bufIndex = 0;
        }

        ptr++;
    }

    if (_currentRow < _rows && bufIndex > 0) {
        lineBuf[bufIndex] = '\0';
        _lcd.setCursor(0, _currentRow++);
        _lcd.print(lineBuf);
    }

    while (_currentRow < _rows) {
        _lcd.setCursor(0, _currentRow++);
        _lcd.print("                    ");
    }

    _currentRow = 0;
}