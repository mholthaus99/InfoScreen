#pragma once
#include <Arduino.h>

/**
 * @brief Weather namespace for fetching and accessing weather data.
 */
namespace Weather
{

    /**
     * @brief Initializes the weather module and fetches initial weather data.
     * 
     * Call this once in setup().
     */
    void init();

    /**
     * @brief Attempts to fetch the latest weather data.
     * 
     * @return true on success, false on failure.
     */
    bool fetch();

    /**
     * @brief Gets a formatted weather summary string.
     * @return C-string, e.g., "City: 72.3F, clear sky"
     */
    const char *getSummary();

    /**
     * @brief Gets the weather description string.
     * @return C-string, e.g., "clear sky"
     */
    const char *getDescription();

    /**
     * @brief Gets the location/city string.
     * @return C-string, e.g., "Kansas City"
     */
    const char *getLocation();

    /**
     * @brief Gets the temperature string.
     * @return C-string, e.g., "72.3F"
     */
    const char *getTemperature();

}
