#pragma once

#include <Arduino.h>
#include <DHT.h>

class DHTSensor {
   public:
    DHTSensor();

    // void begin();
    float getTemperatureF();
    float getHumidity();

    const char* getFormattedTemperature();
    const char* getFormattedHumidity();

   private:
    DHT _dht;
    char _tempBuf[16];
    char _humBuf[16];
};
