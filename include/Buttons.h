#pragma once

#include <functional>
#include <vector>

#define BUTTON_CHANGED_CALLBACK std::function<void(uint8_t, bool)>

enum ButtonMode
{
    WaitForHigh,
    WaitForLow
};

class Buttons
{
public:
    void registerButton(uint8_t pin, ButtonMode mode, BUTTON_CHANGED_CALLBACK callback);
    void setup();
    void loop();

private:
    struct GPIOHandler
    {
    public:
        uint8_t pin;
        ButtonMode mode;
        BUTTON_CHANGED_CALLBACK callback;
        bool lastReportedPressed = false;
        unsigned long lastDebounceTime = 0;
    };

    unsigned long debounceDelay = 50;
    std::vector<GPIOHandler> handlers;

    void checkButton(GPIOHandler handler);
};