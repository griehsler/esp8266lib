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
    class GPIOHandler
    {
    public:
        GPIOHandler(uint8_t pin, ButtonMode mode, BUTTON_CHANGED_CALLBACK callback);
        void setup();
        void loop();

    private:
        uint8_t _pin;
        ButtonMode _mode;
        BUTTON_CHANGED_CALLBACK _callback;
        bool _previouslyPressed;
        bool _lastReportedPressed;
        unsigned long _lastDebounceTime;
        unsigned long debounceDelay = 50;
    };

    std::vector<GPIOHandler *> handlers;
};