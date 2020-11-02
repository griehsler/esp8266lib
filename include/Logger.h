#pragma once

#include <Arduino.h>
#include <WiFiUdp.h>
#include "LoggerSettings.h"
#include "Network.h"

#define LOG_NOTICE "13"
#define LOG_INFO "14"

class Logger
{
public:
  Logger(LoggerSettings * settings);
  void writeLog(String severity, String message);
  void setup(String identity);

private:
  LoggerSettings *_settings;
  String _identity;
  WiFiUDP _UDP;
};
