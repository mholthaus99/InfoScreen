#pragma once
#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include "ir_codes.h"
struct IRCallbacks {
     void (*onPower)();
     void (*onFunction)();
     void (*onSkip)();
     void (*onBack)();
     void (*onPlayPause)();
     void (*onVolumeUp)();
     void (*onVolumeDown)();
     void (*onChannelUp)();
     void (*onChannelDown)();
     void (*onEQ)();
     void (*onRepeat)();
     void (*onDigit)(int digit);
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
          void (**callbackField)();  // Pointer to a function pointer
     };
     IRrecv irrecv;
     decode_results results;
     IRCallbacks registeredCallbacks;
};
