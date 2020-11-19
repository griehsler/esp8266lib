#pragma once

#include "NetworkSettings.h"

class NetworkStatusMonitor
{
public:
  virtual void StartConnectingToOtherAp() {}
  virtual void ProgressConnectingToOtherAp() {}
  virtual void StopConnectingToOtherAp(bool succeeded) {}
  virtual void StartedOwnAp() {}
};

class Network
{
public:
  Network(NetworkSettings *settings);
  Network(NetworkSettings *settings, NetworkStatusMonitor *monitor);
  void setup();
  void loop();

private:
  NetworkSettings *_settings;
  NetworkStatusMonitor *_statusMonitor;
  bool wasConnected = false;
  int reconnectCount = 0;
  bool connectToWifi();
  void startAP();
};
