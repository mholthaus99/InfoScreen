#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "../interfaces/IWeather.h"
#include "secrets.h"

class MyWeather : public IWeather {
   public:
    const char* getCurrentConditions() override;
    const char* getLocation() override;
    const char* getTemperature() override;

    void init() {
        if (!fetch()) {
            Serial.println("Failed to fetch initial weather data");
        }
    }

   private:
    bool fetch();
};