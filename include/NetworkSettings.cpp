#include "NetworkSettings.h"

void NetworkSettings::readFromJson(StaticJsonDocument<512> document)
{
    hostName = document["hostname"].as<String>();
    otherAPSSID = document["ssid"].as<String>();
    otherAPPassword = document["password"].as<String>();
}

void NetworkSettings::writeToJson(StaticJsonDocument<512> document)
{
    document["hostname"] = hostName;
    document["ssid"] = otherAPSSID;
    document["password"] = otherAPPassword;
}