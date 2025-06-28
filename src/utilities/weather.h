#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "../interfaces/IWeather.h"
#include "secrets.h"

class MyWeather {
   public:
    const char* getCurrentConditions();
    const char* getLocation();
    const char* getTemperature();

    void init() {
        if (!fetch()) {
            Serial.println("Failed to fetch initial weather data");
        }
    }

   private:
    bool fetch();
};