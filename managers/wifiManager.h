
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include "config.h"
#include "manager.h"

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

/**
 * Class for controlling wifi connections
 */
class WifiManager : public Manager
{
public:
    WifiManager(ManagerMapper *mappern);

    // connect to wifi, return wifi status 
    uint8_t connect(const char *ssid, const char *passw);
    // disconnect from connected wifi
    void disconnect();
    // ip address
    uint32_t localIP();
};

#endif