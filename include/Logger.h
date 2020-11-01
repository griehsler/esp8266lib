#pragma once

#include "Network.h"
#include <Arduino.h>
#include <WiFiUdp.h>
#include "LoggerSettings.h"

#define LOG_NOTICE "13"
#define LOG_INFO "14"

class Logger
{
public:
  Logger(LoggerSettings * settings);
  void writeLog(String severity, String message);
  void setup();

private:
  LoggerSettings *_settings;
  WiFiUDP _UDP;
};
