#pragma once

class IViewRenderer {
public:
     virtual void drawText(int col, int row, const char* text) = 0;

     // Draws text word-wrapped within the screen dimensions
     virtual void drawWrap(const char* text) = 0;

     // Clears the entire screen or view
     virtual void clear() = 0;

     virtual ~IViewRenderer() {}
};
