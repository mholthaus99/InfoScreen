#pragma once

#include "view.h"
#include "weather.h" // For getprint_weather_summary()
#include "time_utils.h" // For time_getprint()
#include "display.h"

class WeatherView : public View {
public:
    void render() override {
        // Your existing displayWeather logic
        printAt(time_getprint(), 0, 9);
        printAt(getprint_weather_summary(), 2);
    }

    void onBack() override {
        // Logic specific to the weather view when back is pressed
        // For example, navigate back to the default view
        // mode_manager.setMode(MODE_DEFAULT); // Assuming you have a way to change modes
    }

    // Other IR handlers specific to WeatherView, if any
};

