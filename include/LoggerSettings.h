#pragma once

#include <Arduino.h>
#include "NetworkSettings.h"

class LoggerSettings : public virtual NetworkSettings
{
public:
    bool syslogEnabled = false;
    String syslogServer;
    int syslogServerPort = 514;
};