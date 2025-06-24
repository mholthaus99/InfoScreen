#include <Arduino.h>
#pragma once

void weather_init();
bool weather_fetch();
const char* getprint_weather_summary();
const char* getprint_weather_description();
const char* getprint_location();
const char* getprint_temperature();