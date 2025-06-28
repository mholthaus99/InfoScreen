#pragma once
#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include "ir_codes.h"
#include <functional>

#include "../interfaces/IInputDevice.h"

class IRReceiver : public IInputDevice {
public:
     explicit IRReceiver(uint16_t recvPin);

     void begin() override;
     void poll() override;

     // Implement IInputDevice events by forwarding to callbacks:
     void onPower() override;
     void onFunction();
     void onSkip() override;
     void onBack() override;
     void onPlayPause() override;
     void onVolumeUp() override;
     void onVolumeDown() override;
     void onChannelUp() override;
     void onChannelDown() override;
     void onEQ() override;
     void onRepeat() override;
     void onDigit(int digit) override;

     void setCallbacks(const InputCallbacks& callbacks);

private:
     void handleResultCode(uint32_t code);

     struct IRAction {
          uint32_t code;
          const char* label;
          std::function<void()>* callbackField;
     };

     IRrecv irrecv;
     decode_results results;
     InputCallbacks registeredCallbacks;
};
