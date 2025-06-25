#include "weather.h"
#include "secrets.h"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

namespace Weather
{

  static String weatherSummary = "Weather data not yet fetched";
  static String cachedLocation = "Unknown";
  static String cachedTemp = "--F";
  static String cachedDesc = "Unavailable";

  static unsigned long lastWeatherFetchMillis = 0;
  const unsigned long UPDATE_INTERVAL = 10UL * 60UL * 1000UL; // 10 minutes

  bool fetch()
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      weatherSummary = "WiFi not connected";
      cachedLocation = "No WiFi";
      cachedTemp = "--F";
      cachedDesc = "N/A";
      return false;
    }

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = String("https://api.openweathermap.org/data/2.5/weather?zip=64124,us&units=imperial&appid=") + OPENWEATHERMAP_API_KEY;
    http.begin(client, url);

    int httpCode = http.GET();

    if (httpCode == 200)
    {
      String payload = http.getString();
      DynamicJsonDocument doc(payload.length() * 2);

      DeserializationError error = deserializeJson(doc, payload);
      if (!error)
      {
        float temp = doc["main"]["temp"];
        const char *description = doc["weather"][0]["description"];
        const char *city = doc["name"];

        cachedTemp = String(temp, 1) + "F";
        cachedDesc = String(description);
        cachedLocation = String(city);

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%s: %.1fF, %s", city, temp, description);
        weatherSummary = buffer;

        lastWeatherFetchMillis = millis();
        http.end();
        return true;
      }
      else
      {
        weatherSummary = "JSON parse error";
        cachedLocation = "Parse error";
        cachedTemp = "--F";
        cachedDesc = "N/A";
      }
    }
    else
    {
      weatherSummary = String(httpCode) + " Error fetching weather";
      cachedLocation = "HTTP error";
      cachedTemp = "--F";
      cachedDesc = "N/A";
    }

    http.end();
    return false;
  }

  void init()
  {
    fetch(); // Fetch once at startup
  }

  const char *getSummary()
  {
    if (millis() - lastWeatherFetchMillis >= UPDATE_INTERVAL)
    {
      fetch(); // Background refresh
    }
    return weatherSummary.c_str();
  }

  const char *getDescription()
  {
    return cachedDesc.c_str();
  }

  const char *getLocation()
  {
    return cachedLocation.c_str();
  }

  const char *getTemperature()
  {
    return cachedTemp.c_str();
  }

} // namespace Weather
