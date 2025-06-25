#pragma once
#include <Arduino.h>

namespace TimeUtils {

// Call this once in setup to initialize time
void init();

// Returns formatted time string: "HH:MM:SS AM/PM"
const char* getFormattedTime();

}
