
#include <Arduino.h>

#include "system/controller.h"
#include "hd44780_adapter.h"
#include "Wire.h"
#include "hd44780ioClass/hd44780_I2Cexp.h"

//set address
hd44780_I2Cexp rawLcd(0x27);

Hd44780Adapter lcd(rawLcd); 

Controller controller(lcd, 20, 4);

void setup() {
     Wire.begin();
     controller.init();
}

void loop() { controller.loop(); }