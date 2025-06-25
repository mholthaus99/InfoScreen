#pragma once
// Abstract base class
#include "mode_manager.h"
#include "display.h"

class View
{
public:
    virtual ~View() {}

    // Called when the view is shown (optional)
    virtual void onEnter() {}

    // Called when the view is hidden (optional)
    virtual void onExit() {}

    // IR event handlers - override in subclasses
    virtual void onPower() {
        lcd_toggleBacklight();
    }
    virtual void onDigit(int digit) {}
    virtual void onFunction() {
        displayMgr.flagForUpdate(MODE_MENU); // Flag for function mode update
    }
    virtual void onSkip() {}
    virtual void onBack() {}
    virtual void onVolumeUp() {}
    virtual void onVolumeDown() {}
    virtual void onChannelUp() {}
    virtual void onChannelDown() {}
    virtual void onPlayPause() {}
    virtual void onEQ() {}
    virtual void onRepeat() {}

    // Render the view
    virtual void render() = 0;
};
