#pragma once

/**
 * @brief Struct for IR input event callbacks.
 */
struct IRCallbacks {
  void (*onPower)();       ///< Callback for power button press
  void (*onDigit)(int);    ///< Callback for digit button press (0–9)
  void (*onFunction)();    ///< Callback for function button press
  void (*onSkip)();      ///< Callback for skip button press
  void (*onBack)();      ///< Callback for back button press
  void (*onVolumeUp)();  ///< Callback for volume up button press
  void (*onVolumeDown)();///< Callback for volume down button press
  void (*onChannelUp)(); ///< Callback for channel up button press
  void (*onChannelDown)();///< Callback for channel down button press
  void (*onPlayPause)(); ///< Callback for play/pause button press
  void (*onEQ)();        ///< Callback for equalizer button press
  void (*onRepeat)();    ///< Callback for repeat button press
};

/**
 * @brief Initializes the IR receiver.
 */
void ir_init();

/**
 * @brief Polls for new IR input; call this in the main loop.
 */
void ir_poll();

/**
 * @brief Registers all IR event callbacks.
 * 
 * @param callbacks Struct containing function pointers to assign.
 */
void ir_setCallbacks(const IRCallbacks& callbacks);
