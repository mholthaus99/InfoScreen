#pragma once

void dht_init();              // No pin parameter now
float dht_getTemperature();   // Returns Fahrenheit
float dht_getHumidity();
const char* getprint_dht_summary();
const char* getprint_dht_temperature();
const char* getprint_humidity();
