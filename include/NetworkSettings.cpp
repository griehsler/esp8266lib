#include "NetworkSettings.h"

void NetworkSettings::readFromJson(StaticJsonDocument<512> document)
{
    otherAPSSID = document["ssid"].as<String>();
    otherAPPassword = document["password"].as<String>();
}

void NetworkSettings::writeToJson(StaticJsonDocument<512> document)
{
    document["ssid"] = otherAPSSID;
    document["password"] = otherAPPassword;
}