#pragma once

/**
 * @file controller.h
 * @brief High-level system controller: initializes modules, manages views, handles IR input.
 */

/// @brief Initialize all subsystems and views. Call this in `setup()`.
void app_init();

/// @brief Switch to the given view mode.
//void switchView(int mode);

/// @brief Render the currently active view (call in `loop()`).
void renderCurrentMode();

/// @name IR Handlers
/// @{
void irhandle_power();
void irhandle_func();
void irhandle_digit(int digit);
void irhandle_skip();
void irhandle_back();
void irhandle_volume_up();
void irhandle_volume_down();
void irhandle_channel_up();
void irhandle_channel_down();
void irhandle_play_pause();
void irhandle_eq();
void irhandle_repeat();
/// @}
