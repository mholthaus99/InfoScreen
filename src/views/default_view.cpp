#include "default_view.h"


#include "../network/weather.h"
#include "../sensors/dht_sensor.h"


namespace Views
{

  

     void DefaultView::render()
     {
        //  _renderer.drawText(0, 9, timeUtils.getFormattedTime());


          if (millis() - lastToggle >= 5000)
          {
               if (!showingClimate)
               {
                    _renderer.drawText(0,1,"Indoor Climate");
                    _renderer.drawText(0,1,DHTSensor::getFormattedTemperature());
                    _renderer.drawText(0,1, DHTSensor::getFormattedHumidity());
                    showingClimate = true;
               }
               else
               {
                    _renderer.drawText(0,1,Weather::getLocation());
                    _renderer.drawText(0,2,Weather::getDescription());
                    _renderer.drawText(0,3,Weather::getTemperature());
                    showingClimate = false;
               }
               lastToggle = millis();
          }
     }

}  // namespace Views
