#pragma once

#include <Arduino.h>

#include <functional>

#include "../interfaces/IInputDevice.h"
#include "../interfaces/IView.h"
#include "../interfaces/IViewRenderer.h"
#include "../system/menu_view.h"
#include "view_controller.h"

class Controller {
   public:
    /**
     * @brief Constructs the Controller with a renderer and input device.
     * @param renderer The view renderer to use for rendering views.
     * @param inputDevice The input device to handle user inputs.
     */
    Controller(IViewRenderer& renderer, IInputDevice& inputDevice);

    /**
     * @brief Callback type for switching views.
     * This callback is used to switch between different views in the application.
     */
    using SwitchViewCallback = std::function<void(int)>;

    /**
     * @brief Gets the callback for switching views.
     * @return A SwitchViewCallback that can be used to switch views.
     */
    SwitchViewCallback getSwitchViewCallback();

    /**
     * @brief Adds a view to the controller.
     * @param view The view to add.
     */
    void addView(View* view);

    /**
     * @brief Main loop of the controller.
     * Polls the input device and renders the current view.
     */
    void loop();

   private:
    IViewRenderer& _renderer;
    IInputDevice& _inputDevice;
    ViewController _viewController;

    MenuView* _menuView;

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
