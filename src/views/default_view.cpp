#include "default_view.h"

#include "../system/display.h"
#include "../system/mode_manager.h"

#include "../network/weather.h"
#include "../network/time_utils.h"

#include "../sensors/dht_sensor.h"

namespace Views
{

 
    void DefaultView::render()
    {
      

        LCD::printAt(TimeUtils::getFormattedTime(), 0, 9);

        if (millis() - lastToggle >= 5000)
        {
            if (!showingClimate)
            {
                LCD::printAt("Indoor Climate", 1);
                LCD::printAt(DHTSensor::getFormattedTemperature(), 2);
                LCD::printAt(DHTSensor::getFormattedHumidity(), 3);
                showingClimate = true;
            }
            else
            {
                LCD::printAt(Weather::getLocation(), 1);
                LCD::printAt(Weather::getDescription(), 2);
                LCD::printAt(Weather::getTemperature(), 3);
                showingClimate = false;
            }
            lastToggle = millis();
        }
    }

}
