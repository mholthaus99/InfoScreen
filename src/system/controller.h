#pragma once
#include "../interfaces/ILCD.h"
#include "../lcd_renderer.h"
#include "view_controller.h"
#include <Arduino.h>
/**
 * @brief Main application controller for InfoScreen.
 *
 * Handles initialization, main loop, and dispatching IR events to views.
 */
class Controller {
public:
    /**
     * @brief Construct a new Controller object.
     */
    Controller(ILCD& lcd, uint8_t cols, uint8_t rows);

    /**
     * @brief Initialize all hardware and software subsystems.
     *
     * Call this in Arduino's setup().
     */
    void init();

    /**
     * @brief Main application loop.
     *
     * Call this in Arduino's loop(). Handles IR polling and view rendering.
     */
    void loop();

private:
    ILCD& _lcd;

    uint8_t _lcdCols;
    uint8_t _lcdRows;
    LcdRenderer _renderer;
    ViewController viewController;
 


    // Template method definitions should be moved to the header file (controller.h)
    // Remove these from the .cpp file and add them to controller.h as follows:

    // In controller.h, add inside the Controller class:
    template <typename MethodPtr>
    void dispatchIRHandler(MethodPtr method) {
        if (auto view = viewController.getCurrentView()) {
            (view->*method)();
        }
    }

    template <typename MethodPtr, typename Arg>
    void dispatchIRHandler(MethodPtr method, Arg arg) {
        if (auto view = viewController.getCurrentView()) {
            (view->*method)(arg);
        }
    }

    /**
     * @brief Initialize the LCD display.
     */
    void initLCD();

    /**
     * @brief Initialize WiFi and show status on the display.
     */
    void initWiFi();

    /**
     * @brief Initialize time synchronization and show status on the display.
     */
    void initTime();

    /**
     * @brief Initialize IR receiver and register callbacks.
     */
    void initIR();

    /**
     * @brief Initialize sensors (DHT, weather) and show status on the display.
     */
    void initSensors();
};