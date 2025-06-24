#include "weather.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "secrets.h"

// Cached values
static String weatherSummary = "Weather data not yet fetched";
static String cachedLocation = "Unknown";
static String cachedTemp = "--F";
static String cachedDesc = "Unavailable";

static unsigned long lastWeatherFetchMillis = 0;
const unsigned long WEATHER_UPDATE_INTERVAL = 10UL * 60UL * 1000UL; // 10 minutes

/**
 * @brief Fetches the latest weather data from OpenWeatherMap API.
 * 
 * Updates cached weather summary, location, temperature, and description.
 * Handles connection, HTTP, and JSON errors gracefully.
 * 
 * @return true if weather data was successfully fetched and parsed, false otherwise.
 */
bool weather_fetch()
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
    const size_t capacity = payload.length() * 2;
    DynamicJsonDocument doc(capacity);

    if (!deserializeJson(doc, payload))
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

/**
 * @brief Initializes the weather module and fetches the initial weather data.
 */
void weather_init()
{
  weather_fetch();
}

/**
 * @brief Get latest weather summary string.
 * 
 * If the cached data is older than the update interval, attempts to refresh it.
 * 
 * @return Pointer to weather summary C-string.
 */
const char* getprint_weather_summary()
{
  unsigned long now = millis();
  if (now - lastWeatherFetchMillis >= WEATHER_UPDATE_INTERVAL)
  {
    weather_fetch();  // Try to update in the background
  }
  return weatherSummary.c_str();
}

/**
 * @brief Get cached location string.
 * 
 * @return Pointer to location C-string.
 */
const char* getprint_location()
{
  return cachedLocation.c_str();
}

/**
 * @brief Get cached temperature string.
 * 
 * @return Pointer to temperature C-string.
 */
const char* getprint_temperature()
{
  return cachedTemp.c_str();
}

/**
 * @brief Get cached weather description string.
 * 
 * @return Pointer to weather description C-string.
 */
const char* getprint_weather_description(){
  return cachedDesc.c_str();
}