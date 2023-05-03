#pragma once

#include <Arduino.h>
#include <string>

namespace Camcat {
    class Network {
        public:
            Network(String ssid, String password);

            void connect(String ssid, String password);

            bool isConnected() const;

        private:
            bool _isConnected = false;
    };

} // namespace Camcat
