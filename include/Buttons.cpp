#include <Arduino.h>
#include "Buttons.h"

void Buttons::registerButton(uint8_t pin, ButtonMode mode, BUTTON_CHANGED_CALLBACK callback)
{
    GPIOHandler *handler = new GPIOHandler(pin, mode, callback);
    handlers.push_back(handler);
}

void Buttons::setup(unsigned long debounceDelay)
{
    for (auto handler : handlers)
    {
        handler->setup(debounceDelay);
    }
}

void Buttons::loop()
{
    for (auto handler : handlers)
        handler->loop();
}

void Buttons::GPIOHandler::setup(unsigned long debounceDelay)
{
    uint8_t mode;
    if (_mode == ButtonMode::WaitForHigh)
        mode = INPUT;
    else
        mode = INPUT_PULLUP;

    Serial.print("setting up button on pin ");
    Serial.println(_pin);
    pinMode(_pin, mode);

    _debounceDelay = debounceDelay;
}

void Buttons::GPIOHandler::loop()
{
    int newReading = digitalRead(_pin);
    bool newIsPressed = (_mode == ButtonMode::WaitForHigh && newReading == HIGH) ||
                        (_mode == ButtonMode::WaitForLow && newReading == LOW);

    if (newIsPressed != _previouslyPressed)
    {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) >= _debounceDelay)
    {
        if (newIsPressed != _lastReportedPressed)
        {
            Serial.print("reporting new state: ");
            Serial.println(newIsPressed);
            _callback(_pin, newIsPressed);
            _lastReportedPressed = newIsPressed;
        }
    }

    _previouslyPressed = newIsPressed;
}

Buttons::GPIOHandler::GPIOHandler(uint8_t pin, ButtonMode mode, BUTTON_CHANGED_CALLBACK callback)
{
    _pin = pin;
    _mode = mode;
    _callback = callback;

    _previouslyPressed = false;
    _lastReportedPressed = false;
    _lastDebounceTime = millis();
}
