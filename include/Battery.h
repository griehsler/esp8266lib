#pragma once

class Battery
{
public:
    const int minAnalog = 680;
    const int maxAnalog = 940;

    Battery(uint8_t analogPin);
    void setup();
    float measure();

    int measureRaw();
    float normalize(int rawValue);

private:
    uint8_t _analogPin;
};