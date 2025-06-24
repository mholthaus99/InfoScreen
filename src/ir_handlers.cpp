#include "ir_handlers.h"
#include "mode_manager.h"
#include "display.h"
#include <Arduino.h>

/**
 * @brief Handler for the IR power button.
 *
 * Toggles the LCD backlight and prints a message to the display and serial.
 */
void irhandle_power()
{
  Serial.println("Power button pressed (handler)");
  // printAt("Power Toggled!", 0);
  lcd_toggleBacklight();
}

/**
 * @brief Handler for IR digit button presses.
 *
 * If the current mode is MODE_FUNC, performs an action based on the digit:
 *   - 1: Toggle backlight and return to default mode.
 *   - 2: Switch to device info mode.
 *   - 3: Switch to climate mode.
 *   - 4: Return to default mode.
 * else does nothing
 *
 * @param digit The digit button pressed (1-4).
 */
void irhandle_digit(int digit)
{
  Serial.printf("Digit %d pressed (handler)\n", digit);
  if (currentMode != MODE_FUNC)
    return;

  switch (digit)
  {
  case 1:
    lcd_toggleBacklight();
    setMode(MODE_DEFAULT);
    break;
  case 2:
    setMode(MODE_INFO);
    break;
  case 3:
    setMode(MODE_NEWS);
    break;
  case 4:
    setMode(MODE_DEFAULT);
    break;
  }
}

void irhandle_skip()
{
  Serial.println("Skip button pressed (handler)");
  // Implement skip functionality if needed
  if (currentMode == MODE_NEWS){
    //displayMgr.flagForSkip();
    setMode(MODE_NEWS);
  }

}

void irhandle_back()
{
  Serial.println("Back button pressed (handler)");
  // Implement back functionality if needed
  
}

void irhandle_volume_up()
{
  Serial.println("Volume Up button pressed (handler)");
  // Implement volume up functionality if needed
  // For example, increase the volume of a media player
}

void irhandle_volume_down()
{
  Serial.println("Volume Down button pressed (handler)");
  // Implement volume down functionality if needed
  // For example, decrease the volume of a media player
}

void irhandle_channel_up()
{
  Serial.println("Channel Up button pressed (handler)");
  // Implement channel up functionality if needed
  // For example, switch to the next channel in a media player
}

void irhandle_channel_down()
{
  Serial.println("Channel Down button pressed (handler)");
  // Implement channel down functionality if needed
  // For example, switch to the previous channel in a media player
}

void irhandle_play_pause()
{
  Serial.println("Play/Pause button pressed (handler)");
  // Implement play/pause functionality if needed
  // For example, toggle playback of a media player
}

void irhandle_eq()
{
  Serial.println("Equalizer button pressed (handler)");
  // Implement equalizer functionality if needed
  // For example, toggle or adjust the equalizer settings of a media player
}

void irhandle_repeat()
{
  Serial.println("Repeat button pressed (handler)");
  // Implement repeat functionality if needed
  // For example, toggle repeat mode in a media player
}


/**
 * @brief Handler for the IR function button.
 *
 * Switches the display to the function menu mode.
 */
void irhandle_func()
{
  Serial.println("Function button pressed (handler)");
  setMode(MODE_FUNC);
}