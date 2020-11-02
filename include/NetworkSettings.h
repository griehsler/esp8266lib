#pragma once

#include <ArduinoJson.h>

class NetworkSettings
{
public:
    String otherAPSSID;
    String otherAPPassword;
    String hostName;

protected:
    void readFromJson(StaticJsonDocument<512> document);
    void writeToJson(StaticJsonDocument<512> document);
};