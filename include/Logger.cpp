#include "Logger.h"

Logger::Logger(LoggerSettings *settings)
{
    _settings = settings;
}

void Logger::setup(String identity)
{
    if (_settings->syslogEnabled)
    {
        _UDP.begin(2390);
        _identity = identity;
    }
}

void Logger::writeLog(String severity, String message)
{
    if (!_settings->syslogEnabled)
        return;

    _UDP.beginPacket(_settings->syslogServer.c_str(), _settings->syslogServerPort);
    _UDP.write("<");
    _UDP.write(severity.c_str());
    _UDP.write(">");
    _UDP.write(_identity.c_str());
    _UDP.write(" lightswitch[]: ");
    _UDP.write(message.c_str());
    _UDP.endPacket();

#ifdef DEBUG
    Serial.print("Sent syslog message: ");
    Serial.println(message);
#endif
}