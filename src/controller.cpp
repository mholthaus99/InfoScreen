#include "mode_manager.h"
#include "controller.h"

#include "network.h"
#include "ir_receiver.h"

#include "view.h"
#include "news_view.h"
#include "default_view.h"
#include "menu_view.h"

// refactor starting here
View *currentView = nullptr;

void switchView(int mode);

// Declare IR handler function prototypes
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

/**
 * @brief Initializes the application and all hardware/software subsystems.
 *
 * This function should be called in setup(). It initializes serial, LCD, WiFi,
 * time, IR, DHT sensor, and weather modules, and prints status messages to the display.
 */
void app_init()
{
  Serial.begin(115200);
  lcd_init();

  wifi_connect([](const char *status)
               { printMultiLine(status); });

  lcd_clear();
  print("Getting NIST time...");
  time_init();

  printAt("NIST time set", 1);
  printAt("Starting IR...", 2);

  ir_init();
  ir_registerCallbacks({.onPower = irhandle_power,
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
 * @brief Renders the current display mode by calling the appropriate display function.ds
 */
void renderCurrentMode()
{

  if (currentView)
  {
    currentView->render();
  }
}

void switchView(int mode)
{
  if (currentView)
  {
    currentView->onExit();
    delete currentView;
  }

  switch (mode)
  {

  case MODE_DEFAULT:
    currentView = new DefaultView();
    break;

  case MODE_FUNC:
  {
    FunctionView *menuView = new FunctionView(); // functionview needs a callback to switch to news view
    menuView->setSwitchViewCallback(switchView);
    currentView = menuView;
    break;
  }

  case MODE_NEWS:
    currentView = new NewsView();
    break;

  default:
    currentView = new DefaultView(); // Fallback to default view
    break;
  }
  currentView->onEnter();
}

void irhandle_power()
{
  if (currentView)
  {
    currentView->onPower();
  }
}

void irhandle_func()
{
  if (currentView)
  {
    switchView(MODE_FUNC);
  }
}

void irhandle_digit(int digit)
{
  if (currentView)
  {
    currentView->onDigit(digit);
  }
}
void irhandle_skip()
{
  if (currentView)
  {
    currentView->onSkip();
  }
}
void irhandle_back()
{
  if (currentView)
  {
    currentView->onBack();
  }
}
void irhandle_volume_up()
{
  if (currentView)
  {
    currentView->onVolumeUp();
  }
}
void irhandle_volume_down()
{
  if (currentView)
  {
    currentView->onVolumeDown();
  }
}

void irhandle_channel_up()
{
  if (currentView)
  {
    currentView->onChannelUp();
  }
}

void irhandle_channel_down()
{
  if (currentView)
  {
    currentView->onChannelDown();
  }
}

void irhandle_play_pause()
{
  if (currentView)
  {
    currentView->onPlayPause();
  }
}

void irhandle_eq()
{
  if (currentView)
  {
    currentView->onEQ();
  }
}

void irhandle_repeat()
{
  if (currentView)
  {
    currentView->onRepeat();
  }
}

// /**
//  * @brief Displays the device and network information.
//  *
//  * Shows WiFi SSID, password, and IP address.
//  */
// void displayDeviceInfo()
// {
//   if (displayMgr.shouldUpdate(MODE_INFO))
//   {
//     printAt(getprint_wifi_ssid(), 0);
//     printAt(getprint_wifi_password(), 1);
//     printAt(getprint_wifi_ip(), 2);
//     printAt("<>", 3);
//     displayMgr.markUpdated();
//   }
// }