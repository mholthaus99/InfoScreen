#include <Arduino.h>
#pragma once

/// @brief Namespace holding all IR button codes.
namespace IRCodes {
constexpr uint32_t POWER = 0x00FFA25D;
constexpr uint32_t FUNCTION = 0x00FFE21D;
constexpr uint32_t SKIP = 0x00FFC23D;
constexpr uint32_t BACK = 0x00FF22DD;
constexpr uint32_t VOLUME_UP = 0x00FF629D;
constexpr uint32_t VOLUME_DOWN = 0x00FFA857;
constexpr uint32_t CHANNEL_UP = 0x00FF906F;
constexpr uint32_t CHANNEL_DOWN = 0x00FFE01F;
constexpr uint32_t PLAY_PAUSE = 0x00FF02FD;
constexpr uint32_t EQ = 0x00FF9867;
constexpr uint32_t REPEAT = 0x00FFB04F;

/// @brief IR codes for digits 0–9
constexpr uint32_t DIGITS[10] = {
    0xFF6897,  // 0
    0xFF30CF,  // 1
    0xFF18E7,  // 2
    0xFF7A85,  // 3
    0xFF10EF,  // 4
    0xFF38C7,  // 5
    0xFF5AA5,  // 6
    0xFF42BD,  // 7
    0xFF4AB5,  // 8
    0xFF52AD   // 9
};
}  // namespace IRCodes
