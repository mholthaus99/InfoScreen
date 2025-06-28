#pragma once
#include <Arduino.h>
class IViewRenderer {
public:
     virtual void drawText(uint8_t col, uint8_t row, const char* text) = 0;
     virtual void drawText( uint8_t row, const char* text) = 0;
     virtual void drawText(const char* text) = 0;
     virtual void drawWrap(const char* text) = 0;


     virtual void clear() = 0;

     virtual ~IViewRenderer() {}
};
