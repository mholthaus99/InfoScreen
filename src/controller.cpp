#include "mode_manager.h"
#include "controller.h"
#include "network.h"
#include "ir_receiver.h"
#include "view.h"
#include "news_view.h"
#include "default_view.h"
#include "menu_view.h"
#include "dht_sensor.h"
#include "weather.h"
#include "time_utils.h"
#include "display.h"

/// @brief Pointer to the currently active view.
static View *currentView = nullptr;

/**
 * @brief Initializes the application and all hardware/software subsystems.
 * 
 * Should be called in setup(). Initializes serial, LCD, WiFi, time, IR, DHT sensor,
 * and weather modules, and prints status messages to the display.
 */
void app_init()
{
    Serial.begin(115200);
    lcd_init();

    wifi_connect([](const char *status) { printMultiLine(status); });

    lcd_clear();
    print("Getting NIST time...");
    time_init();

    printAt("NIST time set", 1);
    printAt("Starting IR...", 2);

    ir_init();
    ir_registerCallbacks({
        .onPower = irhandle_power,
        .onDigit = irhandle_digit,
        .onFunction = irhandle_func,
        .onSkip = irhandle_skip,
        .onBack = irhandle_back,
        .onVolumeUp = irhandle_volume_up,
        .onVolumeDown = irhandle_volume_down,
        .onChannelUp = irhandle_channel_up,
        .onChannelDown = irhandle_channel_down,
        .onPlayPause = irhandle_play_pause,
        .onEQ = irhandle_eq,
        .onRepeat = irhandle_repeat
    });

    printAt("IR ready", 3);
    lcd_clear();

    printAt("Starting DHT...", 0);
    dht_init();
    printAt("DHT sensor ready", 1);

    printAt("Fetch weather...", 2);
    weather_init();
    printAt("Weather ready", 3);
    lcd_clear();

    switchView(MODE_DEFAULT);
}

/**
 * @brief Renders the current view by calling its render() method.
 */
void renderCurrentMode()
{
    if (currentView)
        currentView->render();
}

/**
 * @brief Switches the current view to the specified mode.
 * 
 * Deletes the previous view and creates a new one based on the mode.
 * Calls onExit() for the old view and onEnter() for the new view.
 * 
 * @param mode The mode to switch to (see DisplayMode enum).
 */
void switchView(int mode)
{
    if (currentView)
    {
        currentView->onExit();
        delete currentView;
        currentView = nullptr;
    }

    switch (mode)
    {
    case MODE_DEFAULT:
        currentView = new DefaultView();
        break;
    case MODE_MENU:
    {
        auto *menuView = new FunctionView();
        menuView->setSwitchViewCallback(switchView);
        currentView = menuView;
        break;
    }
    case MODE_NEWS:
        currentView = new NewsView();
        break;
    case MODE_NETWORK:
        currentView = new DefaultView();
       // displayMgr.markUpdated();
        break;
    default:
        currentView = new DefaultView();
        break;
    }

    if (currentView)
        currentView->onEnter();
}

/**
 * @brief IR handler for the power button.
 * Forwards the event to the current view.
 */
void irhandle_power()
{
    if (currentView)
        currentView->onPower();
}

/**
 * @brief IR handler for the function/menu button.
 * Switches to the function menu view.
 */
void irhandle_func()
{
    switchView(MODE_MENU);
}

/**
 * @brief IR handler for digit buttons.
 * Forwards the event to the current view.
 * @param digit The digit pressed.
 */
void irhandle_digit(int digit)
{
    if (currentView)
        currentView->onDigit(digit);
}

/**
 * @brief IR handler for the skip button.
 * Forwards the event to the current view.
 */
void irhandle_skip()
{
    if (currentView)
        currentView->onSkip();
}

/**
 * @brief IR handler for the back button.
 * Forwards the event to the current view.
 */
void irhandle_back()
{
    if (currentView)
        currentView->onBack();
}

/**
 * @brief IR handler for the volume up button.
 * Forwards the event to the current view.
 */
void irhandle_volume_up()
{
    if (currentView)
        currentView->onVolumeUp();
}

/**
 * @brief IR handler for the volume down button.
 * Forwards the event to the current view.
 */
void irhandle_volume_down()
{
    if (currentView)
        currentView->onVolumeDown();
}

/**
 * @brief IR handler for the channel up button.
 * Forwards the event to the current view.
 */
void irhandle_channel_up()
{
    if (currentView)
        currentView->onChannelUp();
}

/**
 * @brief IR handler for the channel down button.
 * Forwards the event to the current view.
 */
void irhandle_channel_down()
{
    if (currentView)
        currentView->onChannelDown();
}

/**
 * @brief IR handler for the play/pause button.
 * Forwards the event to the current view.
 */
void irhandle_play_pause()
{
    if (currentView)
        currentView->onPlayPause();
}

/**
 * @brief IR handler for the EQ button.
 * Forwards the event to the current view.
 */
void irhandle_eq()
{
    if (currentView)
        currentView->onEQ();
}

/**
 * @brief IR handler for the repeat button.
 * Forwards the event to the current view.
 */
void irhandle_repeat()
{
    if (currentView)
        currentView->onRepeat();
}