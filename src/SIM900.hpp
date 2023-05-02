#pragma once

#include <SD.h>
#include <memory>
#include <string>
#include "Camcat.hpp"

namespace Camcat {

    const short CAMCAT_SIM800L_TX_PIN = 4;
    const short CAMCAT_SIM800L_RX_PIN = 5;

    struct MMSConfig {
        public:
            std::string mmscurl;
            std::string mmsproto;
            std::string apn;
    };

    class Sim900 {
        public:
            Sim900();
            ~Sim900() = default;

            void sendSMS(std::string number, std::string text);
            void sendMMS(
            std::string number, std::string text, std::string image);

        private:
            MMSConfig _mmsConfig;

            void _sendATCommand(std::string command);
            void _setMMSConfig();
            std::string readSerial();
    };
} // namespace Camcat
