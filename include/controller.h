#pragma once

void switchView(int mode);
void renderCurrentMode();
void app_init();  // wraps setup logic

/**
 * @brief Switches the current view to the specified mode.
 * 
 * Deletes the previous view and creates a new one based on the mode.
 * Calls onExit() for the old view and onEnter() for the new view.
 * 
 * @param mode The mode to switch to (see DisplayMode enum).
 */
void switchView(int mode);


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