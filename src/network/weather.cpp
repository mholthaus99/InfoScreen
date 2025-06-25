/**
 * @file weather.cpp
 * @brief Implements weather data fetching and caching for an ESP8266-based project.
 *
 * This module provides functions to fetch current weather data from the OpenWeatherMap API,
 * cache the results, and provide access to weather summary, description, location, and temperature.
 * The data is refreshed at a configurable interval (default: 10 minutes).
 *
 * Dependencies:
 * - ArduinoJson for JSON parsing
 * - ESP8266HTTPClient and WiFiClientSecure for HTTPS requests
 * - ESP8266WiFi for WiFi connectivity
 *
 * Namespace: Weather
 *
 * Static Variables:
 * - weatherSummary: Cached summary string of the latest weather data.
 * - cachedLocation: Cached city/location name.
 * - cachedTemp: Cached temperature string.
 * - cachedDesc: Cached weather description.
 * - lastWeatherFetchMillis: Timestamp of the last successful fetch.
 * - UPDATE_INTERVAL: Interval (ms) between automatic weather data refreshes.
 *
 * Functions:
 * - bool fetch(): Fetches weather data from the API, updates caches, and returns success status.
 * - void init(): Initializes the weather module and performs an initial fetch.
 * - const char* getSummary(): Returns a summary string, refreshing data if needed.
 * - const char* getDescription(): Returns the cached weather description.
 * - const char* getLocation(): Returns the cached location/city name.
 * - const char* getTemperature(): Returns the cached temperature string.
 *
 * Error Handling:
 * - Handles WiFi disconnection, HTTP errors, and JSON parsing errors with appropriate cache updates.
 *
 * Usage:
 * 1. Call Weather::init() at startup.
 * 2. Use getter functions to retrieve weather information as needed.
 */


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
        const char* description = doc["weather"][0]["description"];
        const char* city = doc["name"];

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

  const char* getSummary()
  {
    if (millis() - lastWeatherFetchMillis >= UPDATE_INTERVAL)
    {
      fetch(); // Background refresh
    }
    return weatherSummary.c_str();
  }

  const char* getDescription()
  {
    return cachedDesc.c_str();
  }

  const char* getLocation()
  {
    return cachedLocation.c_str();
  }

  const char* getTemperature()
  {
    return cachedTemp.c_str();
  }

} // namespace Weather
