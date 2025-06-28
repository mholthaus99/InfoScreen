#pragma once
#include <Arduino.h>

#include "../hardware/dht_sensor.h"
#include "../../src/interfaces/IView.h"
#include "../helpers/time_utils.h"
#include "../helpers/weather.h"
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
