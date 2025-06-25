#include "view.h"
#include "display.h"
#include "time_utils.h"
#include "dht_sensor.h"
#include "weather.h"
#include "mode_manager.h"

class DefaultView : public View {
private:
    bool showingClimate = false;
    unsigned long lastToggle = 0;

public:
    void onEnter() override {
        displayMgr.markUpdated();
        showingClimate = false;
        lastToggle = millis() - 5000;  // Force immediate update
        lcd_clear();
    }

    void render() override {
        if (displayMgr.shouldUpdate(MODE_DEFAULT)) {
            displayMgr.markUpdated();
            showingClimate = false;
            lastToggle = millis() - 5000;
            lcd_clear();
        }

        printAt(time_getprint(), 0, 9);

        if (millis() - lastToggle >= 5000) {
            if (!showingClimate) {
                printAt("Indoor Climate", 1);
                printAt(getprint_dht_temperature(), 2);
                printAt(getprint_humidity(), 3);
                showingClimate = true;
            } else {
                printAt(getprint_location(), 1);
                printAt(getprint_weather_description(), 2);
                printAt(getprint_temperature(), 3);
                showingClimate = false;
            }
            lastToggle = millis();
        }
    }

    // Optional: Override IR handlers if needed
    void onBack() override {
        // Example: maybe switch to a function menu
    }

    void onPower() override {
        // Example: toggle backlight or power state
        //lcd_toggleBacklight();
    }
};
