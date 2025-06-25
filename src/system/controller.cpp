#include "controller.h"
#include "view_controller.h"
#include "ir_receiver.h"
#include "../network/network.h"

#include "views/view.h"
#include "views/default_view.h"
#include "views/news_view.h"
#include "views/menu_view.h"

#include "../sensors/dht_sensor.h"
#include "../network/weather.h"
#include "../network/time_utils.h"
#include "../system/display.h"

using namespace Views;

void app_init()
{
    Serial.begin(115200);
    LCD::init();

    WiFiUtils::wifi_connect([](const char *status)
                            { LCD::printMultiLine(status); });

    LCD::clear();
    LCD::print("Getting NIST time...");
    TimeUtils::init();

    LCD::printAt("NIST time set", 1);
    LCD::printAt("Starting IR...", 2);

    ir_init();
    ir_setCallbacks({.onPower = irhandle_power,
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
                          .onRepeat = irhandle_repeat});

    LCD::printAt("IR ready", 3);
    LCD::clear();

    LCD::printAt("Starting DHT...", 0);
    DHTSensor::init();
    LCD::printAt("DHT sensor ready", 1);

    LCD::printAt("Fetch weather...", 2);
    Weather::init();
    LCD::printAt("Weather ready", 3);
    LCD::clear();

    ViewController::setMode(MODE_DEFAULT);
}

void renderCurrentMode()
{

    if (ViewController::getCurrentView())
    {
        ViewController::getCurrentView()->render();
    }
}

void irhandle_power()
{

    ViewController::getCurrentView()->onPower();
}
void irhandle_func()
{

    ViewController::setMode(MODE_MENU);
}
void irhandle_digit(int d)
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onDigit(d);
}
void irhandle_skip()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onSkip();
}
void irhandle_back()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onBack();
}
void irhandle_volume_up()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onVolumeUp();
}
void irhandle_volume_down()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onVolumeDown();
}
void irhandle_channel_up()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onChannelUp();
}
void irhandle_channel_down()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onChannelDown();
}
void irhandle_play_pause()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onPlayPause();
}
void irhandle_eq()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onEQ();
}
void irhandle_repeat()
{
    if (ViewController::getCurrentView())
        ViewController::getCurrentView()->onRepeat();
}
