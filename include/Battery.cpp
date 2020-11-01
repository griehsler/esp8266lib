#include <Arduino.h>
#include "Battery.h"

Battery::Battery(int analogPin)
{
    _analogPin = analogPin;
}

void Battery::setup()
{
    pinMode(_analogPin, INPUT);
}

float Battery::measure()
{
  int analogValue = analogRead(PIN_A0) - minAnalog;
  analogValue = min(maxAnalog, max(minAnalog, analogValue));
  float percentage = ((float)analogValue / (maxAnalog - minAnalog)) * 100;
  return percentage;
}