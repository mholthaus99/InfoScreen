#pragma once

#include "view.h"
#include "display.h"
#include "mode_manager.h"

class FunctionView : public View
{
public:
    using SwitchViewCallback = void (*)(int); // Define a function pointer type

    void setSwitchViewCallback(SwitchViewCallback cb)
    {
        switchViewCallback = cb; // Store the callback
    }

    void render() override
    {
        if (displayMgr.shouldUpdate(MODE_FUNC))
        {
            printAt("1. Toggle Power", 0);
            printAt("2. Internet Settings", 1);
            printAt("3. News", 2);
            printAt("4. Default", 3);
            displayMgr.markUpdated();
        }
    }

    void onBack() override
    {
        setMode(MODE_DEFAULT);
    }

    void onDigit(int digit) override
    {
        Serial.printf("Digit %d pressed in FunctionView\n", digit);
        switch (digit)
        {
        case 1:
            lcd_toggleBacklight();
            setMode(MODE_DEFAULT);
            break;
        case 2:
            setMode(MODE_INFO);
            break;
        case 3:
            setMode(MODE_NEWS);
            if (switchViewCallback)
                switchViewCallback(MODE_NEWS); // Call the callback instead of controller directly
            break;
        case 4:
            setMode(MODE_DEFAULT);
            break;
        default:
            Serial.println("Invalid digit in FunctionView");
            break;
        }
    }

private:
    SwitchViewCallback switchViewCallback = nullptr; // 🔹 DEFINED here
};
