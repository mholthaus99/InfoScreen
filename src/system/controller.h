#pragma once

#include <functional>

#include "../interfaces/IViewRenderer.h"
#include "../interfaces/IView.h"
#include "../interfaces/IInputDevice.h"
#include "view_controller.h"
#include <Arduino.h>

class Controller {
public:
    using SwitchViewCallback = std::function<void(int)>;

    Controller(IViewRenderer& renderer, IInputDevice& inputDevice);

    SwitchViewCallback getSwitchViewCallback();

    void addView(View* view);

    void init();

    void loop();

private:
    IViewRenderer& _renderer;
    IInputDevice& _inputDevice;
    ViewController _viewController;

    void setInputDeviceCallbacks();



    template <typename MethodPtr>
    void dispatchInputHandler(MethodPtr method) {
        if (auto* view = _viewController.getCurrentView()) {
            (view->*method)();
        }
    }

    template <typename Func, typename... Args>
    void dispatchInputHandler(Func method, Args&&... args) {
        if (auto* view = _viewController.getCurrentView()) {
            (view->*method)(std::forward<Args>(args)...);
        }
    }

};


