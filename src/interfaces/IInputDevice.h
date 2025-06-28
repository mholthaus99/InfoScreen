#pragma once

struct InputCallbacks {
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

class IInputDevice {
   public:
    virtual ~IInputDevice() = default;

    virtual void begin() {}
    virtual void poll() = 0;

    // Input events the Controller listens for:
    virtual void onPower() = 0;
    virtual void onFunction() = 0;  // This is the "Menu" button in the context of a TV remote
    // virtual void onMenu() = 0;
    virtual void onSkip() = 0;
    virtual void onBack() = 0;
    virtual void onPlayPause() = 0;
    virtual void onVolumeUp() = 0;
    virtual void onVolumeDown() = 0;
    virtual void onChannelUp() = 0;
    virtual void onChannelDown() = 0;
    virtual void onEQ() = 0;
    virtual void onRepeat() = 0;

    // Digit takes an int parameter
    virtual void onDigit(int digit) = 0;

    virtual void setCallbacks(const InputCallbacks& callbacks) = 0;
};
