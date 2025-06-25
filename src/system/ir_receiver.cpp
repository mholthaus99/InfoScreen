#include "ir_receiver.h"

IRReceiver::IRReceiver(uint16_t recvPin) : irrecv(recvPin), registeredCallbacks{ nullptr } {}

void IRReceiver::begin() { irrecv.enableIRIn(); }

void IRReceiver::poll() {
    if (irrecv.decode(&results)) {
        if (results.value != 0xFFFFFFFFFFFFFFFF) {
            handleResultCode(results.value);
        }
        irrecv.resume();
    }
}

void IRReceiver::setCallbacks(const IRCallbacks& callbacks) { registeredCallbacks = callbacks; }

void IRReceiver::handleResultCode(uint32_t code) {
    static IRAction irActions[] = {
        {IRCodes::POWER, "Power button pressed", &registeredCallbacks.onPower},
        {IRCodes::FUNCTION, "Function button pressed", &registeredCallbacks.onFunction},
        {IRCodes::SKIP, "Skip button pressed", &registeredCallbacks.onSkip},
        {IRCodes::BACK, "Back button pressed", &registeredCallbacks.onBack},
        {IRCodes::PLAY_PAUSE, "Play/Pause button pressed", &registeredCallbacks.onPlayPause},
        {IRCodes::VOLUME_UP, "Volume Up button pressed", &registeredCallbacks.onVolumeUp},
        {IRCodes::VOLUME_DOWN, "Volume Down button pressed", &registeredCallbacks.onVolumeDown},
        {IRCodes::CHANNEL_UP, "Channel Up button pressed", &registeredCallbacks.onChannelUp},
        {IRCodes::CHANNEL_DOWN, "Channel Down button pressed", &registeredCallbacks.onChannelDown},
        {IRCodes::EQ, "Equalizer button pressed", &registeredCallbacks.onEQ},
        {IRCodes::REPEAT, "Repeat button pressed", &registeredCallbacks.onRepeat},
    };

    for (const auto& action : irActions) {
        if (code == action.code) {
            Serial.println(action.label);
            if (*(action.callbackField)) {
                Serial.printf("Executing callback for: %s\n", action.label);
                (*(action.callbackField))();
            }
            return;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (code == IRCodes::DIGITS[i]) {
            Serial.printf("Digit %d pressed\n", i);
            if (registeredCallbacks.onDigit) registeredCallbacks.onDigit(i);
            return;
        }
    }

    Serial.printf("Unknown code: 0x%08X\n", code);
}
