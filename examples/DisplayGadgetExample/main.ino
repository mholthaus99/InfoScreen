#include <Arduino.h>

#include "DisplayGadget.h"

#include "contrib/hardware/lcd_renderer.h"
#include "contrib/hardware/ir_receiver.h"
#include "contrib/hardware/network.h"

#include "contrib/views/default_view.h"
#include "contrib/views/news_view.h"

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
