#pragma once
#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include "ir_codes.h"
#include <functional>

struct IRCallbacks {
     std::function<void()> onPower;
     std::function<void()> onFunction;
     std::function<void()> onSkip;
     std::function<void()> onBack;
     std::function<void()> onPlayPause;
     std::function<void()> onVolumeUp;
     std::function<void()> onVolumeDown;
     std::function<void()> onChannelUp;
     std::function<void()> onChannelDown;
     std::function<void()> onEQ;
     std::function<void()> onRepeat;
     std::function<void(int)> onDigit;
};
class IRReceiver {
public:
     explicit IRReceiver(uint16_t recvPin = D5);
     void begin();
     void poll();
     void setCallbacks(const IRCallbacks& callbacks);

private:
     void handleResultCode(uint32_t code);
     struct IRAction {
          uint32_t code;
          const char* label;
          std::function<void()>* callbackField;
     };
     IRrecv irrecv;
     decode_results results;
     IRCallbacks registeredCallbacks;
};
