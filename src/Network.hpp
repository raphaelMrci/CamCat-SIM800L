#pragma once

#include <Arduino.h>
#include <string>

namespace Camcat {
    class Network {
        public:
            Network(String ssid, String password);

            void sendRequest(String url, String data);
            void connect(String ssid, String password);

        private:
            String _ssid;
            String _password;
            bool _isConnected = false;
    };

} // namespace Camcat
