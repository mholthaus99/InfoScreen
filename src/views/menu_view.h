#pragma once

#include <Arduino.h>

#include <functional>

#include "../interfaces/IView.h"
#include "../interfaces/IViewRenderer.h"
#include "../system/view_controller.h"  // or wherever it's defined

class MenuView : public View {
public:
    /**
     * @brief Callback to ViewController to switch views.
     */
    using SwitchViewCallback = std::function<void(int)>;

    /**
     * @brief Sets the callback to switch views.
     */
   
    MenuView(SwitchViewCallback switchViewCallback)
        : _switchViewCallback(switchViewCallback) {}
    /**
     * @brief Overridden: Called when the view is entered.
     */
    void onEnter() override;

    /**
     * @brief Overridden: Handles the "back" event to switch to DefaultView.
     */
    void onBack() override;

    /**
     * @brief Overridden: Handles the "function" event to switch to DefaultView.
     */
    void onFunction() override;

    /**
     * @brief Overridden: Handles digit input to switch views.
     * @param digit The digit pressed (1, 2, or 3).
     */
    void onDigit(int digit) override;

    /**
     * @brief Overridden: Renders the FunctionView.
     */
    void render() override;

private:
    /**
     * @brief Calls the callback to switch views.
     * @param index The index of the view to switch to.
     */
    void setViewControllerIndex(int index) {
        if (_switchViewCallback) {
            _switchViewCallback(index);
        }
    }

    /**
     * @brief Callback to switch views in the ViewController.
     */
    SwitchViewCallback _switchViewCallback;  // Callback to switch views
};
