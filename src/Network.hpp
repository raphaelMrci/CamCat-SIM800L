
#pragma once

#include <string>

// Http client
class Network
{
  public:
    Network(std::string ssid, std::string password);

    void sendRequest(std::string url, std::string data);
    void connect(std::string ssid, std::string password);

  private:
    std::string _ssid;
    std::string _password;
    bool _isConnected = false;
};
