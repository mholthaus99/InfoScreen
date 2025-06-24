#include "mode_manager.h"
#include "controller.h"
#include "network.h"
#include "time_utils.h"
#include "ir_receiver.h"
#include "dht_sensor.h"
#include "weather.h"
#include "ir_handlers.h"
#include "rss_reader.h"

/**
 * @brief Tracks whether the default screen is showing climate (1) or weather (0).
 */
int showingClimate = 0;

/**
 * @brief Timestamp of the last toggle between climate and weather on the default screen.
 */
unsigned long lastDefaultToggle = 0;

/**
 * @brief Timestamp of the last change to the title on the news display.
 */
unsigned long timeOfLastTitleChange = 0;


static void displayDefault();
static void displayWeather();
static void displayClimate();
static void displayFuncMenu();
static void displayDeviceInfo();
static void displayNews();

/**
 * @brief Renders the current display mode by calling the appropriate display function.
 */
void renderCurrentMode() {
  switch (currentMode) {
    case MODE_DEFAULT: displayDefault(); break;
    case MODE_WEATHER: displayWeather(); break;
    case MODE_CLIMATE: displayClimate(); break;
    case MODE_FUNC: displayFuncMenu(); break;
    case MODE_INFO: displayDeviceInfo(); break;
    case MODE_NEWS: displayNews(); break;
    default: break;
  }
}

/**
 * @brief Initializes the application and all hardware/software subsystems.
 * 
 * This function should be called in setup(). It initializes serial, LCD, WiFi,
 * time, IR, DHT sensor, and weather modules, and prints status messages to the display.
 */
void app_init() {
  Serial.begin(115200);
  lcd_init();
  lastDefaultToggle = millis() - 5000;

  wifi_connect([](const char *status) {
    printMultiLine(status);
  });

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

  

}

/**
 * @brief Displays the default screen, toggling between climate and weather every 5 seconds.
 * 
 * Shows the current time at the top right, and alternates between indoor climate
 * and weather information on the lower lines.
 */
void displayDefault()
{
  if (displayMgr.shouldUpdate(MODE_DEFAULT))
  {
    displayMgr.markUpdated();
    showingClimate = 0;
    lastDefaultToggle = millis() - 5000;
    lcd_clear();
  }

  printAt(time_getprint(), 0, 9);

  if (millis() - lastDefaultToggle >= 5000)
  {
    if (showingClimate == 0)
    {
      printAt("Indoor Climate", 1);
      printAt(getprint_dht_temperature(), 2);
      printAt(getprint_humidity(), 3);
      showingClimate = 1;
    }
    else
    {
      printAt(getprint_location(), 1);
      printAt(getprint_weather_description(), 2);
      printAt(getprint_temperature(), 3);
      showingClimate = 0;
    }

    lastDefaultToggle = millis();
  }
}

void displayNews()
{
  if (displayMgr.shouldUpdate(MODE_NEWS))
  {
    printWrapped(rss_getprint_headline()); // This will update the headline
    timeOfLastTitleChange = millis();
    displayMgr.markUpdated();
  }

  if(millis() - timeOfLastTitleChange >= 5000)
  {
    timeOfLastTitleChange = millis();
    
    printWrapped(rss_getprint_headline()); // This will update the headline
  }

}


/**
 * @brief Displays the current weather information.
 * 
 * Shows the current time and a summary of the weather.
 */
void displayWeather()
{
  if (displayMgr.shouldUpdate(MODE_WEATHER))
  {
    printAt(time_getprint(), 0, 9);
    printAt(getprint_weather_summary(), 2);
    displayMgr.markUpdated();
  }
}

/**
 * @brief Displays the indoor climate data.
 * 
 * Shows the current time and a summary of temperature and humidity.
 */
void displayClimate()
{
  if (displayMgr.shouldUpdate(MODE_CLIMATE))
  {
    printAt(time_getprint(), 0, 9);
    printAt(getprint_dht_summary(), 2);
    displayMgr.markUpdated();
  }
}

/**
 * @brief Displays the function menu.
 * 
 * Shows a list of available functions for the user to select.
 */
void displayFuncMenu()
{
  if (displayMgr.shouldUpdate(MODE_FUNC))
  {
    printAt("1. Toggle Power", 0);
    printAt("2. Internet Settings", 1);
    printAt("3. News", 2);
    printAt("4. Default", 3);
    displayMgr.markUpdated();
  }
}

/**
 * @brief Displays the device and network information.
 * 
 * Shows WiFi SSID, password, and IP address.
 */
void displayDeviceInfo()
{
  if (displayMgr.shouldUpdate(MODE_INFO))
  {
    printAt(getprint_wifi_ssid(), 0);
    printAt(getprint_wifi_password(), 1);
    printAt(getprint_wifi_ip(), 2);
    printAt("<>", 3);
    displayMgr.markUpdated();
  }
}