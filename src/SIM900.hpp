#pragma once

#include <Arduino.h>
#include <SD.h>
#include <memory>
#include <string>
#include "Camcat.hpp"

namespace Camcat {

    const short CAMCAT_SIM800L_TX_PIN = 4;
    const short CAMCAT_SIM800L_RX_PIN = 5;

    struct MMSConfig {
        public:
            String mmscurl;
            String mmsproto;
            String apn;
    };

    class Sim900 {
        public:
            Sim900(Camcat::Config &config);
            ~Sim900() = default;

            void sendSMS(String number, String text);
            void sendMMS(String number, String text, String image);

        private:
            MMSConfig _mmsConfig;
            Camcat::Config _config;

            void _sendATCommand(String command);
            void _setMMSConfig();
            void _unlockSIM();
            String readSerial();
    };
} // namespace Camcat
