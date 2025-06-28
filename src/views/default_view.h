#pragma once
#include <Arduino.h>

#include "../imp/dht_sensor.h"
#include "../interfaces/IView.h"
#include "../utilities/time_utils.h"
#include "../utilities/weather.h"
class DefaultView : public View {
   public:
    DefaultView();
    void render() override;

   private:
    TimeUtils _time;
    DHTSensor _sensor;
    MyWeather _weather;
    bool showingClimate = false;
    unsigned long lastToggle = 0;
};
