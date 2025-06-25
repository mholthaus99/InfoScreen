#include "default_view.h"

#include "../network/time_utils_instance.h"
#include "../network/weather.h"
#include "../sensors/dht_sensor.h"
#include "../system/display_instance.h"

namespace Views
{
     void DefaultView::render()
     {
          lcd.printAt(timeUtils.getFormattedTime(), 0, 9);

          if (millis() - lastToggle >= 5000)
          {
               if (!showingClimate)
               {
                    lcd.printAt("Indoor Climate", 1);
                    lcd.printAt(DHTSensor::getFormattedTemperature(), 2);
                    lcd.printAt(DHTSensor::getFormattedHumidity(), 3);
                    showingClimate = true;
               }
               else
               {
                    lcd.printAt(Weather::getLocation(), 1);
                    lcd.printAt(Weather::getDescription(), 2);
                    lcd.printAt(Weather::getTemperature(), 3);
                    showingClimate = false;
               }
               lastToggle = millis();
          }
     }

}  // namespace Views
