
#include <Arduino.h>
#include "secrets.h"
#include "system/controller.h"
#include "hd44780_adapter.h"
#include "lcd_renderer.h"
#include "Wire.h"
#include "hd44780ioClass/hd44780_I2Cexp.h"

#include "network/time_utils.h"
#include "network/network.h"


//set address
hd44780_I2Cexp rawLcd(0x27);

Hd44780Adapter lcd(rawLcd, 20, 4); 

LcdRenderer renderer(lcd);

Controller controller(renderer);

TimeUtils timeUtils;
WiFiManager wifi;



void setup() {
     Serial.begin(115200);

     Wire.begin();
     lcd.begin();

     wifi.setCredentials(WIFI_SSID,WIFI_PASS);
     wifi.init();

     timeUtils.init();

     controller.init();

}

void loop() { controller.loop(); }