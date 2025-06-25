#include "controller.h"

#include "../network/network.h"
#include "../network/time_utils_instance.h"
#include "../network/weather.h"
#include "../sensors/dht_sensor.h"
#include "../system/display_instance.h"
#include "ir_receiver.h"
#include "view_controller.h"

IRReceiver irReceiver;

using namespace Views;

void Controller::init() {
     Serial.begin(115200);
     initLCD();
     initWiFi();
     initTime();
     initIR();
     initSensors();

     ViewController::setMode(MODE_DEFAULT);
}

void Controller::loop() {
     irReceiver.poll();

     if (auto view = ViewController::getCurrentView()) {
          view->render();
     }
}

template <typename MethodPtr>
void Controller::dispatchIRHandler(MethodPtr method) {
     if (auto view = ViewController::getCurrentView()) {
          (view->*method)();
     }
}

template <typename MethodPtr, typename Arg>
void Controller::dispatchIRHandler(MethodPtr method, Arg arg) {
     if (auto view = ViewController::getCurrentView()) {
          (view->*method)(arg);
     }
}

void Controller::initLCD() { lcd.init(); }

void Controller::initWiFi() {
     WiFiUtils::wifi_connect([](const char* status) { lcd.printMultiLine(status); });
}

void Controller::initTime() {
     lcd.print("Getting NIST time...");
     timeUtils.init();
     lcd.printAt("NIST time set", 1);
}

void Controller::initIR() {
     lcd.printAt("Starting IR...", 2);
     irReceiver.begin();

     irReceiver.setCallbacks(
          { []() { dispatchIRHandler(&View::onPower); }, []() { ViewController::setMode(MODE_MENU); },
           []() { dispatchIRHandler(&View::onSkip); }, []() { dispatchIRHandler(&View::onBack); },
           []() { dispatchIRHandler(&View::onPlayPause); },
           []() { dispatchIRHandler(&View::onVolumeUp); },
           []() { dispatchIRHandler(&View::onVolumeDown); },
           []() { dispatchIRHandler(&View::onChannelUp); },
           []() { dispatchIRHandler(&View::onChannelDown); },
           []() { dispatchIRHandler(&View::onEQ); }, []() { dispatchIRHandler(&View::onRepeat); },
           [](int d) { dispatchIRHandler(&View::onDigit, d); } });

     lcd.printAt("IR ready", 3);
     lcd.clear();
}

void Controller::initSensors() {
     lcd.printAt("Starting DHT...", 0);
     DHTSensor::init();
     lcd.printAt("DHT sensor ready", 1);

     lcd.printAt("Fetch weather...", 2);
     Weather::init();
     lcd.printAt("Weather ready", 3);
     lcd.clear();
}
