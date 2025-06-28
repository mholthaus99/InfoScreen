#include "dht_sensor.h"

DHTSensor::DHTSensor() : _dht(D6, DHT11) {  // Default pin D6 and type DHT11
    _dht.begin();
}

float DHTSensor::getTemperatureF() {
    float tempC = _dht.readTemperature();
    if (isnan(tempC)) return NAN;
    return (tempC * 9.0f / 5.0f) + 32.0f;
}

float DHTSensor::getHumidity() {
    float hum = _dht.readHumidity();
    if (isnan(hum)) return NAN;
    return hum;
}

const char* DHTSensor::getFormattedTemperature() {
    float tempF = getTemperatureF();
    if (!isnan(tempF)) {
        snprintf(_tempBuf, sizeof(_tempBuf), "%.1fF", tempF);
    } else {
        snprintf(_tempBuf, sizeof(_tempBuf), "Temp error");
    }
    return _tempBuf;
}

const char* DHTSensor::getFormattedHumidity() {
    float hum = getHumidity();
    if (!isnan(hum)) {
        snprintf(_humBuf, sizeof(_humBuf), "%.1f%%", hum);
    } else {
        snprintf(_humBuf, sizeof(_humBuf), "Hum error");
    }
    return _humBuf;
}
