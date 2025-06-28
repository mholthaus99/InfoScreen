/**
 * @file controller.cpp
 * @brief Implements the main application controller for InfoScreen.
 */

#include "controller.h"

Controller::Controller(IViewRenderer& renderer, IInputDevice& inputDevice)
    : _renderer(renderer), _inputDevice(inputDevice), _viewController(renderer) {

    // Construct MenuView with internal callback
    _menuView = new MenuView([this](int index) {
        _viewController.switchTo(index);
        });

    addView(_menuView);
    _viewController.switchTo(0);  // Start on MenuView
    setInputDeviceCallbacks();
}


void Controller::addView(View* view) {
    _viewController.addView(view);
    view->setViewRenderer(&_renderer);
}

void Controller::loop() {
    _inputDevice.poll();
    if (auto view = _viewController.getCurrentView()) {
        view->render();
    }
}

void Controller::setInputDeviceCallbacks() {
    _inputDevice.setCallbacks({ [this]() { dispatchInputHandler(&View::onPower); },
                               [this]() { _viewController.switchTo(0); },
                               [this]() { dispatchInputHandler(&View::onSkip); },
                               [this]() { dispatchInputHandler(&View::onBack); },
                               [this]() { dispatchInputHandler(&View::onPlayPause); },
                               [this]() { dispatchInputHandler(&View::onVolumeUp); },
                               [this]() { dispatchInputHandler(&View::onVolumeDown); },
                               [this]() { dispatchInputHandler(&View::onChannelUp); },
                               [this]() { dispatchInputHandler(&View::onChannelDown); },
                               [this]() { dispatchInputHandler(&View::onEQ); },
                               [this]() { dispatchInputHandler(&View::onRepeat); },
                               [this](int d) { dispatchInputHandler(&View::onDigit, d); } });
}
