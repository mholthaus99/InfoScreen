#include <Arduino.h>
#include "system/controller.h"
#include "system/view_controller.h"

#include "imp/ir_receiver.h"
#include "imp/lcd_renderer.h"
#include "imp/dht_sensor.h"
#include "imp/network.h"
#include "utilities/weather.h"
#include "utilities/time_utils.h"

#include "views/menu_view.h"  
#include "views/default_view.h"
#include "views/news_view.h"


Hd44780LcdRenderer renderer(0x27, 20, 4); // I2C address 0x27, 20 columns, 4 rows
IRReceiver inputController(D5); 
Controller controller(renderer, inputController);

static WiFiManager wifiManager;

static DHTSensor dhtSensor(D6, DHT11); // Pin D6 for DHT11 sensor
static MyWeather weather;
static TimeUtils timeUtils;

static DefaultView defaultView(timeUtils, dhtSensor, weather);
static FunctionView functionView;
static NewsView newsView; // Declare NewsView instance

void setup() {


     Serial.begin(115200);

     renderer.begin();

     renderer.drawText("Welcome to InfoScreen!");
     renderer.drawText("Starting wifi...");
     

     wifiManager.setCredentials(WIFI_SSID, WIFI_PASS);
     wifiManager.connect();
     renderer.drawText("WiFi Manager initialized");
     delay(1000); // Give some time for WiFi to connect
    
     inputController.begin();
     renderer.drawText("Input Controller initialized");
     delay(1000); // Allow time for input controller to initialize
     renderer.begin();
     renderer.drawText("Renderer initialized");

     dhtSensor.begin();
     weather.init();
     timeUtils.init();


     controller.addView(&functionView);
     renderer.drawText("View added");

     controller.addView(&defaultView);
     renderer.drawText("Default View added");

     controller.addView(&newsView); // Dynamically allocate NewsView

     functionView.setSwitchViewCallback(controller.getSwitchViewCallback());
     renderer.drawText("Callback set");
     delay(1000);

     controller.init();
     renderer.drawText("Controller initialized");



}

void loop() {
     controller.loop();
}
