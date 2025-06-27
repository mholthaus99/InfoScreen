#include "menu_view.h"


#include <Arduino.h> // For Serial.printf
#include <functional>

namespace Views
{

    void FunctionView::setSwitchViewCallback(SwitchViewCallback cb)
    {
        switchViewCallback = cb;
    }

    void FunctionView::onEnter()
    {

        // lcdextern.printAt("1. Default", 0);
        // lcdextern.printAt("2. Local News", 1);
        // lcdextern.printAt("3. Network", 2);
    }

    void FunctionView::onBack()
    {
       // ViewController::setMode(MODE_DEFAULT);
        if (switchViewCallback)
            switchViewCallback(MODE_DEFAULT);
    }

    void FunctionView::onFunction()
    {
       // ViewController::setMode(MODE_DEFAULT);
        if (switchViewCallback)
            switchViewCallback(MODE_DEFAULT);
    }

    void FunctionView::onDigit(int digit)
    {
        Serial.printf("Digit %d pressed in FunctionView\n", digit);
        switch (digit)
        {
        case 1:
          //  ViewController::setMode(MODE_DEFAULT);
            if (switchViewCallback)
                switchViewCallback(MODE_DEFAULT);
            break;
        case 2:
          //  ViewController::setMode(MODE_NEWS);
            if (switchViewCallback)
                switchViewCallback(MODE_NEWS);
            break;
        case 3:
           // ViewController::setMode(MODE_DEFAULT); // You might want a MODE_NETWORK or similar
            if (switchViewCallback)
                switchViewCallback(MODE_DEFAULT);
            break;
        default:
            Serial.println("Invalid digit in FunctionView");
            break;
        }
    }

    void FunctionView::render() {
        return;
    }

} // namespace Views
