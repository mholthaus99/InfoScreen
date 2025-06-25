#include "menu_view.h"
#include "../system/display.h"
#include "../system/mode_manager.h"
#include <Arduino.h> // For Serial.printf

namespace Views {

void FunctionView::setSwitchViewCallback(SwitchViewCallback cb)
{
    switchViewCallback = cb;
}

void FunctionView::render()
{
    if (displayMgr.shouldUpdate(MODE_MENU))
    {
        LCD::printAt("1. Default", 0);
        LCD::printAt("2. Local News", 1);
        LCD::printAt("3. Network", 2);
        displayMgr.markUpdated();
    }
}

void FunctionView::onBack()
{
    setMode(MODE_DEFAULT);
    if (switchViewCallback)
        switchViewCallback(MODE_DEFAULT);
}

void FunctionView::onDigit(int digit)
{
    Serial.printf("Digit %d pressed in FunctionView\n", digit);
    switch (digit)
    {
    case 1:
        setMode(MODE_DEFAULT);
        if (switchViewCallback)
            switchViewCallback(MODE_DEFAULT);
        break;
    case 2:
        setMode(MODE_NEWS);
        if (switchViewCallback)
            switchViewCallback(MODE_NEWS);
        break;
    case 3:
        setMode(MODE_DEFAULT); // You might want a MODE_NETWORK or similar
        if (switchViewCallback)
            switchViewCallback(MODE_DEFAULT);
        break;
    default:
        Serial.println("Invalid digit in FunctionView");
        break;
    }
}

}  // namespace Views
