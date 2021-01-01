#pragma once

#include <ArduinoJson.h>

class LoggerSettings
{
public:
    bool syslogEnabled = false;
    String syslogServer;
    int syslogServerPort = 514;

protected:
    void readFromJson(const JsonDocument &document);
    void writeToJson(JsonDocument &document);
};