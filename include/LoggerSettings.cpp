#include "LoggerSettings.h"

void LoggerSettings::readFromJson(const JsonDocument &document)
{
    syslogEnabled = document["syslogEnabled"].as<bool>();
    syslogServer = document["syslogServer"].as<String>();
    syslogServerPort = document["syslogServerPort"].as<int>();
}

void LoggerSettings::writeToJson(JsonDocument &document)
{
    document["syslogEnabled"] = syslogEnabled;
    document["syslogServer"] = syslogServer;
    document["syslogServerPort"] = syslogServerPort;
}