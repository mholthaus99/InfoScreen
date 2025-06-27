#pragma once
#include "./interfaces/IViewRenderer.h"
#include "./interfaces/ILCD.h"

class LcdRenderer : public IViewRenderer {
public:
    LcdRenderer(ILCD& lcd, uint8_t cols, uint8_t rows)
        : _lcd(lcd), _cols(cols), _rows(rows), _col(0), _row(0) {
    }

    void drawText(int col, int row, const char* text) override {
        _lcd.setCursor(col, row);
        _lcd.print(text);
        _col = col;
        _row = row;
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

private:
    ILCD& _lcd;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _col = 0;
    uint8_t _row = 0;

    void newline() {
        _col = 0;
        _row = (_row + 1) % _rows; // wrap to top
        _lcd.setCursor(_col, _row);
    }
};
