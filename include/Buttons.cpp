#include <Arduino.h>
#include "Buttons.h"

void Buttons::registerButton(uint8_t pin, ButtonMode mode, BUTTON_CHANGED_CALLBACK callback)
{
    GPIOHandler handler;
    handler.pin = pin;
    handler.mode = mode;
    handler.callback = callback;
    handlers.push_back(handler);
}

void Buttons::setup()
{
    for (auto handler : handlers)
    {
        uint8_t mode;
        if (handler.mode == ButtonMode::WaitForHigh)
            mode = INPUT_PULLUP;
        else
            mode = INPUT_PULLUP;

        pinMode(handler.pin, mode);
    }
}

void Buttons::loop()
{
    for (auto handler : handlers)
        checkButton(handler);
}

void Buttons::checkButton(GPIOHandler handler)
{
    int newReading = digitalRead(handler.pin);
    bool newIsPressed = (handler.mode == ButtonMode::WaitForHigh && newReading == HIGH) ||
                        (handler.mode == ButtonMode::WaitForLow && newReading == LOW);

    if (newIsPressed != handler.lastReportedPressed)
        handler.lastReportedPressed = millis();

    if ((millis() - handler.lastDebounceTime) > debounceDelay)
    {
        if (newIsPressed != handler.lastReportedPressed)
        {
            handler.callback(handler.pin, newIsPressed);
            handler.lastReportedPressed = newIsPressed;
        }
    }
}