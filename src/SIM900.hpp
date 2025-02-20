#pragma once

#include <Arduino.h>
#include <SD.h>
#include <memory>
#include <string>
#include "Camcat.hpp"

namespace Camcat {
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

            void sendSMS(String text);
            void sendMMS(String text, String image);

        private:
            Camcat::MMSConfig _mmsConfig;
            Camcat::Config _config;

            void _sendATCommand(String command);
            void _setMMSConfig();
            void _unlockSIM();
            String readSerial();
    };
} // namespace Camcat
