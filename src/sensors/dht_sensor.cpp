#include "dht_sensor.h"
#include <DHT.h>
#include <Arduino.h>

#define DHTTYPE DHT11
constexpr uint8_t DHTPIN = D6; ///< Pin used for DHT sensor

namespace DHTSensor
{

  static DHT dht(DHTPIN, DHTTYPE); // Fully initialize here

  // Internal static buffers for formatted output
  static char dhtTempBuf[16];
  static char dhtHumBuf[16];

  void init()
  {
    dht.begin();
  }

  float getTemperatureF()
  {
    float tempC = dht.readTemperature();
    if (isnan(tempC))
      return NAN;
    return (tempC * 9.0 / 5.0) + 32.0;
  }

  float getHumidity()
  {
    float hum = dht.readHumidity();
    if (isnan(hum))
      return NAN;
    return hum;
  }

  const char *getFormattedTemperature()
  {
    float tempF = getTemperatureF();
    if (!isnan(tempF))
    {
      snprintf(dhtTempBuf, sizeof(dhtTempBuf), "%.1fF", tempF);
    }
    else
    {
      snprintf(dhtTempBuf, sizeof(dhtTempBuf), "Temp error");
    }
    return dhtTempBuf;
  }

  const char *getFormattedHumidity()
  {
    float hum = getHumidity();
    if (!isnan(hum))
    {
      snprintf(dhtHumBuf, sizeof(dhtHumBuf), "%.1f%%", hum);
    }
    else
    {
      snprintf(dhtHumBuf, sizeof(dhtHumBuf), "Hum error");
    }
    return dhtHumBuf;
  }

}
