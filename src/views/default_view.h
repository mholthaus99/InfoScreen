#pragma once
#include <Arduino.h>

#include "../imp/dht_sensor.h"
#include "../interfaces/ITime.h"
#include "../interfaces/IView.h"
#include "../interfaces/IViewRenderer.h"
#include "../interfaces/IWeather.h"
class DefaultView : public View {
   public:
    void render() override;
    DefaultView(ITime& time, DHTSensor& sensor, IWeather& weather)
        : _time(time), _sensor(sensor), _weather(weather) {}

   private:
    ITime& _time;
    DHTSensor& _sensor;
    IWeather& _weather;
    bool showingClimate = false;
    unsigned long lastToggle = 0;
};
