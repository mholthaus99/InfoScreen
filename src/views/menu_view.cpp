#include "menu_view.h"

void MenuView::onEnter() {
    if (_viewRenderer == nullptr) {
        Serial.println("FunctionView: _viewRenderer is null, cannot render.");
        return;
    }
    _viewRenderer->drawText(0, "1. Default");
    _viewRenderer->drawText(1, "2. Local News");
    _viewRenderer->drawText(2, "3. Network");
}

void MenuView::onBack() {
    setViewControllerIndex(0);  // Switch to DefaultView
}

void MenuView::onFunction() {
    setViewControllerIndex(0);  // Switch to DefaultView
}

void MenuView::onDigit(int digit) {
    Serial.printf("Digit %d pressed in FunctionView\n", digit);
    switch (digit) {
    case 1:
        setViewControllerIndex(1);  // Switch to DefaultView
        break;
    case 2:
        setViewControllerIndex(2);  // Switch to DefaultView
        break;
    case 3:
        setViewControllerIndex(3);  // Switch to DefaultView
        break;
    default:
        Serial.println("Invalid digit in FunctionView");
        break;
    }
}

void MenuView::render() {}
