#pragma once

#include <Arduino.h>
#include <DHT.h>

class DHTSensor {
   public:
    DHTSensor(uint8_t pin, uint8_t type = DHT11);

    void begin();
    float getTemperatureF();
    float getHumidity();

    const char* getFormattedTemperature();
    const char* getFormattedHumidity();

   private:
    DHT _dht;
    char _tempBuf[16];
    char _humBuf[16];
};
