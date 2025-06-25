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
        if (displayMgr.shouldUpdate(MODE_MENU))
        {
            printAt("1. Default", 0);
            printAt("2. Local News", 1);
            printAt("3. Network", 2);
            //printAt("4. ", 3);
            displayMgr.markUpdated();
        }
    }

    void onBack() override
    {
        setMode(MODE_DEFAULT);
        if(switchViewCallback)
            switchViewCallback(MODE_DEFAULT); // Call the callback instead of controller directly
    }

    void onDigit(int digit) override
    {
        Serial.printf("Digit %d pressed in FunctionView\n", digit);
        switch (digit)
        {
        case 1:
          
            setMode(MODE_DEFAULT);
            if (switchViewCallback)
                switchViewCallback(MODE_DEFAULT); // Call the callback instead of controller directly
            break;
        case 2:
            setMode(MODE_NEWS);
            if (switchViewCallback)
                switchViewCallback(MODE_NEWS); // Call the callback instead of controller directly
            break;
        case 3:
            setMode(MODE_DEFAULT);
            if (switchViewCallback)
                switchViewCallback(MODE_DEFAULT); // Call the callback instead of controller directly
            break;
      
        default:
            Serial.println("Invalid digit in FunctionView");
            break;
        }
    }

private:
    SwitchViewCallback switchViewCallback = nullptr; // 🔹 DEFINED here
};
