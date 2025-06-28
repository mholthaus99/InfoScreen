#include "default_view.h"

void DefaultView::render() {
    _viewRenderer->drawText(0, _time.getFormattedTime());
    if (millis() - lastToggle >= 5000) {
        if (!showingClimate) {
            _viewRenderer->drawText(1, "Indoor Climate");
            _viewRenderer->drawText(2, _sensor.getFormattedTemperature());
            _viewRenderer->drawText(3, _sensor.getFormattedHumidity());
            showingClimate = true;
        } else {
            _viewRenderer->drawText(1, _weather.getLocation());
            _viewRenderer->drawText(2, _weather.getCurrentConditions());
            _viewRenderer->drawText(3, _weather.getTemperature());
            showingClimate = false;
        }
        lastToggle = millis();
    }
}
