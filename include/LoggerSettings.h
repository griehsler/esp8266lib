#pragma once

#include <ArduinoJson.h>

class LoggerSettings
{
public:
    bool syslogEnabled = false;
    String syslogServer;
    int syslogServerPort = 514;

protected:
    void readFromJson(StaticJsonDocument<1024> document);
    void writeToJson(StaticJsonDocument<1024> document);
};