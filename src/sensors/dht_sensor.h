#pragma once

namespace DHTSensor
{

    void init(); // Call during setup()

    // Formatted string accessors (e.g., "72.3F", "55.0%")
    const char *getFormattedTemperature();
    const char *getFormattedHumidity();

    float getTemperatureF(); // Returns Fahrenheit
    float getHumidity();     // Returns relative humidity %

}
