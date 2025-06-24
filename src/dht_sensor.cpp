#include "dht_sensor.h"
#include <DHT.h>
#include <Arduino.h>

#define DHTTYPE DHT11
constexpr uint8_t DHTPIN = D6;  ///< Pin used for DHT sensor

/// @brief DHT sensor object (DHT11 on D6)
static DHT dht(DHTPIN, DHTTYPE);  // Fully initialize here

/**
 * @brief Initialize the DHT sensor.
 * 
 * Call this in setup() before reading temperature or humidity.
 */
void dht_init() {
  dht.begin();
}

/**
 * @brief Get the current temperature from the DHT sensor in Fahrenheit.
 * 
 * @return Temperature in Fahrenheit, or NAN if reading fails.
 */
float dht_getTemperature() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return NAN;
  }
  return (temp * 9.0 / 5.0) + 32.0;  // Convert to Fahrenheit
}

/**
 * @brief Get the current humidity from the DHT sensor.
 * 
 * @return Relative humidity in percent, or NAN if reading fails.
 */
float dht_getHumidity() {
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return NAN;
  }
  return hum;
}

static char dhtBuf[21];  ///< Static buffer to hold the formatted summary string

/**
 * @brief Get a formatted summary string of temperature and humidity.
 * 
 * @return Pointer to a static buffer containing "xx.xF xx.x%" or "Sensor error".
 */
const char* getprint_dht_summary() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    float tempF = (temp * 9.0 / 5.0) + 32.0;
    snprintf(dhtBuf, sizeof(dhtBuf), "%.1fF %.1f%%", tempF, hum);
  } else {
    snprintf(dhtBuf, sizeof(dhtBuf), "Sensor error");
  }

  return dhtBuf;
}

char dhtTempBuf[16];  ///< Static buffer for formatted temperature string
char dhtHumBuf[16];   ///< Static buffer for formatted humidity string

/**
 * @brief Get a formatted temperature string for display.
 * 
 * @return Pointer to a static buffer containing "xx.xF" or "Temp error".
 */
const char* getprint_dht_temperature() {
  float temp = dht.readTemperature();
  if (!isnan(temp)) {
    float tempF = (temp * 9.0 / 5.0) + 32.0;
    snprintf(dhtTempBuf, sizeof(dhtTempBuf), "%.1fF", tempF);
  } else {
    snprintf(dhtTempBuf, sizeof(dhtTempBuf), "Temp error");
  }
  return dhtTempBuf;
}

/**
 * @brief Get a formatted humidity string for display.
 * 
 * @return Pointer to a static buffer containing "xx.x%" or "Hum error".
 */
const char* getprint_humidity() {
  float hum = dht.readHumidity();
  if (!isnan(hum)) {
    snprintf(dhtHumBuf, sizeof(dhtHumBuf), "%.1f%%", hum);
  } else {
    snprintf(dhtHumBuf, sizeof(dhtHumBuf), "Hum error");
  }
  return dhtHumBuf;
}