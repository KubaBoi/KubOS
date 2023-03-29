#include "wifiManager.h"

WifiManager::WifiManager(ManagerMapper *mappern) : Manager(mappern, "WIF")
{
    WiFi.mode(WIFI_STA);
}

uint8_t WifiManager::connect(const char *ssid, const char *passw)
{
    WiFi.begin(ssid, passw);
    log("Connecting to '%s'...", ssid);
    while (WiFi.status() == 6) {}
    log("Wifi status: %d", WiFi.status());
    return WiFi.status();
}

void WifiManager::disconnect()
{
}

uint32_t WifiManager::localIP() { return WiFi.localIP(); }