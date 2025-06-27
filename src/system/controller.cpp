#include "controller.h"

#include "../network/network.h"
#include "../network/time_utils_instance.h"
#include "../network/weather.h"
#include "../sensors/dht_sensor.h"
//#include "../system/display_instance.h"
#include "ir_receiver.h"
#include "view_controller.h"

IRReceiver irReceiver;


using namespace Views;

Controller::Controller(ILCD& lcd, uint8_t cols, uint8_t rows)
     : _lcd(lcd), _lcdCols(cols), _lcdRows(rows), _renderer(_lcd, 20, 4), viewController(_renderer)
{

}

void Controller::init() {
     Serial.begin(115200);
     initLCD();
     initWiFi();
     initTime();
     initIR();
     initSensors();

     viewController.setMode(MODE_DEFAULT);

}

void Controller::loop() {
     irReceiver.poll();

     if (auto view = viewController.getCurrentView()) {
          view->render();
     }
}



void Controller::initLCD() { _lcd.begin(_lcdCols, _lcdRows); }

void Controller::initWiFi() {
     WiFiUtils::wifi_connect();
}

void Controller::initTime() {
     _lcd.print("Getting NIST time...");
     timeUtils.init();
     _lcd.print("NIST time set");
}

void Controller::initIR() {
     _lcd.print("Starting IR");
     irReceiver.begin();

     irReceiver.setCallbacks(
          {
              [this]() { dispatchIRHandler(&View::onPower); },
              [this]() { viewController.setMode(MODE_MENU); },
              [this]() { dispatchIRHandler(&View::onSkip); },
              [this]() { dispatchIRHandler(&View::onBack); },
              [this]() { dispatchIRHandler(&View::onPlayPause); },
              [this]() { dispatchIRHandler(&View::onVolumeUp); },
              [this]() { dispatchIRHandler(&View::onVolumeDown); },
              [this]() { dispatchIRHandler(&View::onChannelUp); },
              [this]() { dispatchIRHandler(&View::onChannelDown); },
              [this]() { dispatchIRHandler(&View::onEQ); },
              [this]() { dispatchIRHandler(&View::onRepeat); },
              [this](int d) { dispatchIRHandler(&View::onDigit, d); }
          }
     );

     _lcd.print("IR ready");
     _lcd.clear();
}

void Controller::initSensors() {
     _lcd.print("Starting DHT...");
     DHTSensor::init();
     _lcd.print("DHT sensor ready");

     _lcd.print("Fetch weather...");
     Weather::init();
     _lcd.print("Weather ready");
     _lcd.clear();
}
