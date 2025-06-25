#include "mode_manager.h"

/// @brief Global display manager instance.
ModeManager displayMgr;

/// @brief Tracks the current display mode.
DisplayMode currentMode = MODE_DEFAULT;

/**
 * @brief Marks the display as updated (no update needed).
 *
 * Sets the internal flag to indicate the display is up to date.
 */
void ModeManager::markUpdated()
{
  needsUpdateFlag = false;
}

/**
 * @brief Flags the display for update and records the new mode.
 *
 * Sets the internal flag to request a display update and stores the last mode.
 * Also clears the LCD display.
 *
 * @param mode The new display mode to set.
 */
void ModeManager::flagForUpdate(DisplayMode mode)
{
  needsUpdateFlag = true;
  lastMode = mode;
  // lcd_clear();
}

// void ModeManager::flagForSkip()
// {
//   needsUpdateFlag = true;
//   // lastMode = MODE_COUNT; // Reset last mode to force update
// }

/**
 * @brief Checks if the display should be updated for the given mode.
 *
 * Returns true if the display is flagged for update or if the mode has changed.
 * Special handling for the initial default mode.
 *
 * @param mode The display mode to check.
 * @return true if an update is needed, false otherwise.
 */
bool ModeManager::shouldUpdate(DisplayMode mode)
{
  if (mode == MODE_DEFAULT && lastMode == MODE_COUNT)
  {
    lastMode = MODE_DEFAULT;
    return true;
  }
  return needsUpdateFlag || mode != lastMode;
}

/**
 * @brief Sets the current display mode and flags the display for update.
 *
 * @param mode The new display mode to set.
 */
void setMode(DisplayMode mode)
{
  currentMode = mode;
  displayMgr.flagForUpdate(mode);
}