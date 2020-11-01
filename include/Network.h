#pragma once

#include "NetworkSettings.h"

class Network
{
public:
  Network(NetworkSettings *settings);
  void setup();
  void loop();

private:
  NetworkSettings *_settings;
  bool wasConnected = false;
  int reconnectCount = 0;
  bool connectToWifi();
  void startAP();
};