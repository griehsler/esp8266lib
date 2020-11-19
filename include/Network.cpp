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
  WiFi.begin(_settings->otherAPSSID.c_str(), _settings->otherAPPassword.c_str());

  for (int i = 0; i < 120; i++)
  {
    Serial.print(".");
    if (WiFi.isConnected())
    {
      Serial.println("");
      Serial.print("connected, IP Address: ");
      Serial.println(WiFi.localIP());
      wasConnected = true;
      reconnectCount = 0;
      _statusMonitor->StopConnectingToOtherAp(true);
      return true;
    }
    _statusMonitor->ProgressConnectingToOtherAp();
    delay(500);
  }

  Serial.println("");
  Serial.println("timed out.");
  _statusMonitor->StopConnectingToOtherAp(false);
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
