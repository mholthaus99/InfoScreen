#include "controller.h"


Controller::Controller(IViewRenderer& viewRenderer) : _viewRenderer(viewRenderer), viewController(viewRenderer) {}

void Controller::init() {
     
     initIR();

     viewController.setMode(MODE_DEFAULT);

}

void Controller::loop() {
     irReceiver.poll();

     if (auto view = viewController.getCurrentView()) {
          view->render();
     }
}



void Controller::initIR() {
     _viewRenderer.drawText(0, 0, "Starting IR");
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

     _viewRenderer.drawText(0, 0, "IR ready");
     // _lcd.clear();
}


