#pragma once

#include <Arduino.h>
#include "Network.hpp"
#include "SDReader.hpp"
#include "SIM900.hpp"

namespace Camcat {
    class Controller {
        public:
            Controller();
            ~Controller();

            // void setup();
            // void loop();

        private:
            Camcat::Network *_network;
            Camcat::SDReader *_sdReader;
            Camcat::Sim900 *_sim900;
    };
} // namespace Camcat
