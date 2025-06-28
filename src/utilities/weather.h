#pragma once
#include <Arduino.h>

#include "secrets.h"
#include "../interfaces/IWeather.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

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