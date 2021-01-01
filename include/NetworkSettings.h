#pragma once

#include <ArduinoJson.h>

class NetworkSettings
{
public:
    String otherAPSSID;
    String otherAPPassword;
    String hostName;

    String staticIP;
    String gateway;
    String subnet;
    String dns1;
    String dns2;

protected:
    void readFromJson(const JsonDocument &document);
    void writeToJson(JsonDocument &document);
};