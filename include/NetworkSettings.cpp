#include "NetworkSettings.h"

void NetworkSettings::readFromJson(const JsonDocument &document)
{
    hostName = document["hostname"].as<String>();
    otherAPSSID = document["ssid"].as<String>();
    otherAPPassword = document["password"].as<String>();

    staticIP = document["staticip"].as<String>();
    gateway = document["gateway"].as<String>();
    subnet = document["subnet"].as<String>();
    dns1 = document["dns1"].as<String>();
    dns2 = document["dns2"].as<String>();
}

void NetworkSettings::writeToJson(JsonDocument &document)
{
    document["hostname"] = hostName;
    document["ssid"] = otherAPSSID;
    document["password"] = otherAPPassword;

    document["staticip"] = staticIP;
    document["gateway"] = gateway;
    document["subnet"] = subnet;
    document["dns1"] = dns1;
    document["dns2"] = dns2;
}