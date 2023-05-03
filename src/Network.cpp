#include "Network.hpp"
#include <WiFi.h>
#include "Camcat.hpp"

Camcat::Network::Network(String ssid, String password)
{
    if (WiFi.status() == WL_CONNECTED) {
        CAMCAT_DEBUG_PRINTLN("Already connected");
        return;
    }
    connect(ssid, password);
}

void Camcat::Network::connect(String ssid, String password)
{
    CAMCAT_DEBUG_PRINT("Connecting to WiFi network : ");
    CAMCAT_DEBUG_PRINTLN(ssid.c_str());

    // Check if WiFi is already connected
    if (WiFi.status() == WL_CONNECTED) {
        CAMCAT_DEBUG_PRINTLN("Already connected");
        // Disconnect WiFi
        WiFi.disconnect();
        _isConnected = false;
    }

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        CAMCAT_DEBUG_PRINT(".");
        delay(500);
    }

    _isConnected = true;
    CAMCAT_DEBUG_PRINTLN("");
    CAMCAT_DEBUG_PRINTLN("WiFi connected");
    CAMCAT_DEBUG_PRINT("IP address: ");
    CAMCAT_DEBUG_PRINTLN(WiFi.localIP());
}

bool Camcat::Network::isConnected() const
{
    return _isConnected;
}
