/**
 * @file main.cpp
 * @brief Entry point for the InfoScreen application.
 *
 * Initializes hardware, sets up the LCD and view system, and starts the main controller loop.
 */

#include <Arduino.h>
#include "system/controller.h"
#include "system/view_controller.h"
#include "hd44780_adapter.h"
#include "lcd_renderer.h"
#include "views/menu_view.h"  // Provides FunctionView
#include "Wire.h"
#include "system/ir_receiver.h"

 // LCD setup
hd44780_I2Cexp rawLcd(0x27);
Hd44780Adapter lcd(rawLcd, 4, 20);
LcdRenderer renderer(lcd);

// Views that depend on the ViewController
static FunctionView functionView;

// Use IRReceiver dir   ectly if it is not abstract
IRReceiver inputController(D5); // Pin 5 for IR receiver

// Main application controller 
Controller controller(renderer, inputController);

/**
 * @brief Arduino setup function.
 * Initializes serial, I2C, LCD, views, and controller.
 */
void setup() {

          inputController.begin();

          Serial.begin(115200);
          delay(100);
          Serial.println("Start setup");

          Wire.begin();
          Serial.println("Wire.begin done");

          lcd.begin();
          Serial.println("lcd.begin done");

          controller.addView(&functionView);
          Serial.println("View added");

          functionView.setSwitchViewCallback(controller.getSwitchViewCallback());
          Serial.println("Callback set");

          controller.init();
          Serial.println("Controller initialized");

      
     
}

/**
 * @brief Arduino main loop.
 * Delegates to the main controller loop.
 */
void loop() {
     controller.loop();
}
