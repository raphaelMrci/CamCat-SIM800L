#include "Network.hpp"
#include "Camcat.hpp"
#include <HTTPClient.h>
#include <WiFi.h>

Network::Network(std::string ssid, std::string password)
{
    if (WiFi.status() == WL_CONNECTED) {
        CAMCAT_DEBUG_PRINTLN("Already connected");
        return;
    }
    connect(ssid, password);
}

void Network::connect(std::string ssid, std::string password)
{
    CAMCAT_DEBUG_PRINT("Connecting to WiFi network : ");
    CAMCAT_DEBUG_PRINTLN(ssid.c_str());

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        CAMCAT_DEBUG_PRINT(".");
        delay(500);
    }

    CAMCAT_DEBUG_PRINTLN("");
    CAMCAT_DEBUG_PRINTLN("WiFi connected");
    CAMCAT_DEBUG_PRINT("IP address: ");
    CAMCAT_DEBUG_PRINTLN(WiFi.localIP());
}
