#include "ir_receiver.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "ir_codes.h"
#include <IRutils.h>
#include <Arduino.h>

/// @brief IR receiver pin
constexpr uint16_t IR_RECV_PIN = D5;

/// @brief IR receiver instance
static IRrecv irrecv(IR_RECV_PIN);

/// @brief IR decode results storage
static decode_results results;

/// @brief Currently registered IR callbacks
static IRCallbacks registeredCallbacks = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};



struct IRAction {
  uint32_t code;
  const char* label;
  void (**callbackField)();  // pointer to pointer!
};

static const IRAction irActions[] = {
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


/**
 * @brief Internal handler for decoded IR codes.
 *
 * @param code The received IR code.
 */
static void handleResultCode(uint32_t code)
{

for (const auto& action : irActions)
{
  if (code == action.code)
  {
    Serial.println(action.label);
    if (*(action.callbackField))
    {
      Serial.printf("Executing callback for: %s\n", action.label);
      (*(action.callbackField))();  // Dereference and call
    }
    return;
  }
}


  for (int i = 0; i < 10; ++i)
  {
    if (code == IRCodes::DIGITS[i])
    {
      Serial.printf("Digit %d pressed\n", i);
      if (registeredCallbacks.onDigit)
        registeredCallbacks.onDigit(i);
      return;
    }
  }

  Serial.printf("Unknown code: 0x%08X\n", code);
}

/**
 * @brief Initializes the IR receiver hardware.
 */
void ir_init()
{
  irrecv.enableIRIn();
}

/**
 * @brief Polls the IR receiver and handles input if available.
 *
 * Call this from the main `loop()` function.
 */
void ir_poll()
{
  if (irrecv.decode(&results))
  {
    if (results.value != 0xFFFFFFFFFFFFFFFF)
    {
      handleResultCode(results.value);
    }
    irrecv.resume();
  }
}

/**
 * @brief Registers callback functions for IR events.
 *
 * @param callbacks Struct containing the callbacks for power, digits, and function buttons.
 */
void ir_setCallbacks(const IRCallbacks &callbacks)
{
  registeredCallbacks = callbacks;
}
