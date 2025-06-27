#pragma once

#include "lcd_renderer.h"
#include "../views/view.h"

enum DisplayMode {
     MODE_DEFAULT,
     MODE_MENU,
     MODE_NEWS,
     MODE_NETWORK
};

class ViewController {
public:
     explicit ViewController(LcdRenderer& renderer);

     void setMode(DisplayMode mode);
     DisplayMode getMode() const;
     Views::View* getCurrentView() const;

private:
     void switchView(DisplayMode mode);

     DisplayMode currentMode = MODE_DEFAULT;
     Views::View* currentView = nullptr;
     LcdRenderer& renderer;
};
