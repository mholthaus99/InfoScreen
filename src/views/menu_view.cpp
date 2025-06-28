#include "menu_view.h"
#include <Arduino.h>


void FunctionView::onEnter() {
    if (_viewRenderer == nullptr) {
        Serial.println("FunctionView: _viewRenderer is null, cannot render.");
        return;
    }
    _viewRenderer->drawTextonLine(0, "1. Default");
    _viewRenderer->drawTextonLine(1, "2. Local News");
    _viewRenderer->drawTextonLine(2, "3. Network");
}

void FunctionView::onBack() {
    setViewControllerIndex(0); // Switch to DefaultView
}

void FunctionView::onFunction() {
    setViewControllerIndex(0); // Switch to DefaultView
}

void FunctionView::onDigit(int digit) {
    Serial.printf("Digit %d pressed in FunctionView\n", digit);
    switch (digit) {
    case 1:
        setViewControllerIndex(0); // Switch to DefaultView
        break;
    case 2:
        setViewControllerIndex(1); // Switch to DefaultView
        break;
    case 3:
        setViewControllerIndex(2); // Switch to DefaultView
        break;
    default:
        Serial.println("Invalid digit in FunctionView");
        break;
    }
}

void FunctionView::render() {


}
