#pragma once

class Battery
{
public:
    int minAnalog = 680;
    int maxAnalog = 940;

    Battery(int analogPin);
    void setup();
    float measure();

private:
    int _analogPin;
};