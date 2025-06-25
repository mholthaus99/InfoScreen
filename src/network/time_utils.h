/**
 * @file time_utils.h
 * @brief Utility functions for time initialization and formatting.
 *
 * This header provides functions to initialize the system time and retrieve
 * a formatted time string for display purposes.
 *
 * Namespace: TimeUtils
 *
 * Functions:
 * - void init(): Initializes the system time. Should be called once in setup.
 * - const char* getFormattedTime(): Returns the current time as a formatted string ("HH:MM:SS AM/PM").
 */
#pragma once
#include <Arduino.h>

namespace TimeUtils
{

    // Call this once in setup to initialize time
    void init();

    // Returns formatted time string: "HH:MM:SS AM/PM"
    const char *getFormattedTime();

}
