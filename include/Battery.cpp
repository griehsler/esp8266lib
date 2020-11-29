#include <Arduino.h>
#include "Battery.h"

Battery::Battery(uint8_t analogPin)
{
  _analogPin = analogPin;
}

void Battery::setup()
{
  pinMode(_analogPin, INPUT);
}

int Battery::measureRaw()
{
  return analogRead(_analogPin);
}

float Battery::normalize(int rawValue)
{
  int analogValue = min(maxAnalog, max(minAnalog, rawValue));
  analogValue = maxAnalog - analogValue;
  float percentage = ((float)analogValue / (maxAnalog - minAnalog)) * 100;
  return percentage;
}

float Battery::measure()
{
  return normalize(measureRaw());
}