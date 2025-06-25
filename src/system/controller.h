#pragma once

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
    Controller() = default;

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
    /**
     * @brief Dispatch an IR event handler method to the current view.
     *
     * @tparam MethodPtr Pointer to a view member function.
     * @param method The member function pointer to call.
     */
    template <typename MethodPtr>
    static void dispatchIRHandler(MethodPtr method);

    /**
     * @brief Dispatch an IR event handler method with an argument to the current view.
     *
     * @tparam MethodPtr Pointer to a view member function.
     * @tparam Arg Argument type.
     * @param method The member function pointer to call.
     * @param arg The argument to pass to the handler.
     */
    template <typename MethodPtr, typename Arg>
    static void dispatchIRHandler(MethodPtr method, Arg arg);

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