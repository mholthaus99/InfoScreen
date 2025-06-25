#include "controller.h"
#include "mode_manager.h"
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

static View* currentView = nullptr;

void app_init()
{
    Serial.begin(115200);
    LCD::init();

    
    
    WiFiUtils::wifi_connect([](const char *status) {
        LCD::printMultiLine(status);
    });

    LCD::clear();
    LCD::print("Getting NIST time...");
    TimeUtils::init();

    LCD::printAt("NIST time set", 1);
    LCD::printAt("Starting IR...", 2);

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

    LCD::printAt("IR ready", 3);
    LCD::clear();

    LCD::printAt("Starting DHT...", 0);
    DHTSensor::init();
    LCD::printAt("DHT sensor ready", 1);

    LCD::printAt("Fetch weather...", 2);
    Weather::init();
    LCD::printAt("Weather ready", 3);
    LCD::clear();

    switchView(MODE_DEFAULT);
}

void renderCurrentMode()
{
    if (currentView)
        currentView->render();
}

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
        auto *menu = new FunctionView();
        menu->setSwitchViewCallback(switchView);
        currentView = menu;
        break;
    }
    case MODE_NEWS:
        currentView = new NewsView();
        break;
    case MODE_NETWORK:
        currentView = new DefaultView(); // TODO: create NetworkView later
        break;
    default:
        currentView = new DefaultView();
        break;
    }

    if (currentView)
        currentView->onEnter();
}

// === IR Event Dispatching ===

void irhandle_power()        { if (currentView) currentView->onPower(); }
void irhandle_func()         { switchView(MODE_MENU); }
void irhandle_digit(int d)   { if (currentView) currentView->onDigit(d); }
void irhandle_skip()         { if (currentView) currentView->onSkip(); }
void irhandle_back()         { if (currentView) currentView->onBack(); }
void irhandle_volume_up()    { if (currentView) currentView->onVolumeUp(); }
void irhandle_volume_down()  { if (currentView) currentView->onVolumeDown(); }
void irhandle_channel_up()   { if (currentView) currentView->onChannelUp(); }
void irhandle_channel_down() { if (currentView) currentView->onChannelDown(); }
void irhandle_play_pause()   { if (currentView) currentView->onPlayPause(); }
void irhandle_eq()           { if (currentView) currentView->onEQ(); }
void irhandle_repeat()       { if (currentView) currentView->onRepeat(); }
