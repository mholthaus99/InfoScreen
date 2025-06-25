#include "system/view_controller.h"
#include "system/controller.h"
#include "system/ir_receiver.h"
#include <Arduino.h>

/**
 * @brief Arduino setup function.
 * 
 * Initializes all hardware and software subsystems for the InfoScreen application.
 * Calls app_init() to perform consolidated setup.
 */
void setup() {
  app_init();  // Consolidate all setup logic into one function
}

/**
 * @brief Arduino main loop function.
 * 
 * Continuously polls the IR receiver for input and renders the current display mode.
 * The display logic is delegated to renderCurrentMode().
 */
void loop() {
  ir_poll();
  renderCurrentMode();  // Move display logic into display_modes.cpp
}