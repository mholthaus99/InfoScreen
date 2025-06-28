#pragma once
#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>

#include <functional>

#include "../interfaces/IInputDevice.h"
#include "ir_codes.h"

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

    /**
     * @brief Struct to hold IR action codes and their associated labels and callbacks.
     */
    struct IRAction {
        uint32_t code;
        const char* label;
        std::function<void()>* callbackField;
    };

    /**
     * @brief IRrecv instance to handle IR signals.
     */
    IRrecv irrecv;

    /**
     * @brief Decoded results from the IR receiver.
     */
    decode_results results;

    /**
     * @brief Registered input callbacks.
     */
    InputCallbacks registeredCallbacks;
};
