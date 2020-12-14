#include "Network.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

Network::Network(NetworkSettings *settings)
{
  NetworkStatusMonitor *defaultMonitor = new NetworkStatusMonitor();

  _settings = settings;
  _statusMonitor = defaultMonitor;
}

Network::Network(NetworkSettings *settings, NetworkStatusMonitor *monitor)
{
  _settings = settings;
  _statusMonitor = monitor;
}

void Network::setup()
{
  if (!_settings->otherAPSSID || _settings->otherAPSSID == "" || !connectToWifi())
    startAP();
  else
  {
    if (!MDNS.begin(_settings->hostName.c_str(), WiFi.localIP()))
      Serial.println("Error setting up mDNS responder for device name '" + _settings->hostName + "'!");
    else
      Serial.println("mDNS responder for device name " + _settings->hostName + ".local started.");
  }
}

bool Network::connectToWifi()
{
  Serial.print("trying to connect to '" + _settings->otherAPSSID + "' ");

  _statusMonitor->StartConnectingToOtherAp();

  WiFi.mode(WIFI_STA);
  WiFi.hostname(_settings->hostName);

  if (_settings->staticIP && _settings->staticIP != "")
  {
    IPAddress staticIP;
    IPAddress gateway;
    IPAddress subnet;
    if (staticIP.fromString(_settings->staticIP) &&
        gateway.fromString(_settings->gateway) &&
        subnet.fromString(_settings->subnet))
    {
      IPAddress dns1;
      IPAddress dns2;
      if (!dns1.fromString(_settings->dns1))
        dns1 = (uint32_t)0;
      if (!dns2.fromString(_settings->dns2))
        dns2 = (uint32_t)0;

      if (!WiFi.config(staticIP, gateway, subnet, dns1, dns2))
      {
        Serial.println("failed to configure!");
        return false;
      }
    }
    else
    {
      Serial.println("Failed to parse static IP configuration, IP='" + _settings->staticIP +
                     "' gateway='" + _settings->gateway +
                     "' subnet='" + _settings->subnet +
                     "'.");
      return false;
    }
  }

  if (tryConnect(5000, 5))
  {
    wasConnected = true;
    reconnectCount = 0;
    _statusMonitor->StopConnectingToOtherAp(true);
    return true;
  }

  if (!WiFi.getAutoConnect())
    WiFi.setAutoConnect(true);
  if (!WiFi.getPersistent())
    WiFi.persistent(true);

  WiFi.begin(_settings->otherAPSSID.c_str(), _settings->otherAPPassword.c_str());

  if (tryConnect(60000, 500))
  {
    wasConnected = true;
    reconnectCount = 0;
    _statusMonitor->StopConnectingToOtherAp(true);
    return true;
  }
  _statusMonitor->StopConnectingToOtherAp(false);
  return false;
}

bool Network::tryConnect(int timeoutMs, int delayMs)
{
  int tries = timeoutMs / delayMs;
  for (int i = 0; i < tries; i++)
  {
    Serial.print(".");
    if (WiFi.isConnected())
    {
      Serial.println("");
      Serial.print("connected, IP Address: ");
      Serial.println(WiFi.localIP());
      return true;
    }
    _statusMonitor->ProgressConnectingToOtherAp();
    delay(delayMs);
  }

  Serial.println("");
  Serial.println("timed out.");
  return false;
}

void Network::startAP()
{
  String ssid = "SwitchIt" + String(ESP.getFlashChipId());
  IPAddress ip(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  Serial.println("starting WIFI AP");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(ssid.c_str(), "Test1234");
  Serial.println("started WIFI AP '" + ssid + "'");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  _statusMonitor->StartedOwnAp();
}

void Network::loop()
{
  if (wasConnected && !WiFi.isConnected())
  {
    Serial.println("lost connection to WIFI!");
    if (!connectToWifi())
    {
      reconnectCount++;
      Serial.print("failed for ");
      Serial.print(reconnectCount);
      Serial.println(" times!");

      if (reconnectCount >= 10)
      {
        Serial.println("falling back to AP mode.");
        startAP();
      }
    }
  }
}
