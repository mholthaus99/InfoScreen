#include <Arduino.h>

#include "imp/ir_receiver.h"
#include "imp/lcd_renderer.h"
#include "imp/network.h"
#include "system/controller.h"
#include "system/view_controller.h"
#include "views/default_view.h"
#include "views/news_view.h"

Hd44780LcdRenderer renderer; 
IRReceiver inputController;
Controller controller(renderer, inputController);

static WiFiManager wifiManager;

void setup() {
    Serial.begin(115200);

    renderer.drawText("Starting InfoScreen...");
    wifiManager.begin(WIFI_SSID, WIFI_PASS);

    controller.addView(new DefaultView());
    controller.addView(new NewsView());
}

void loop() {
    controller.loop();
}
