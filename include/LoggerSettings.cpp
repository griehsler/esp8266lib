#include "LoggerSettings.h"

void LoggerSettings::readFromJson(StaticJsonDocument<1024> document)
{
    syslogEnabled = document["syslogEnabled"].as<bool>();
    syslogServer = document["syslogServer"].as<String>();
    syslogServerPort = document["syslogServerPort"].as<int>();
}

void LoggerSettings::writeToJson(StaticJsonDocument<1024> document)
{
    document["syslogEnabled"] = syslogEnabled;
    document["syslogServer"] = syslogServer;
    document["syslogServerPort"] = syslogServerPort;
}