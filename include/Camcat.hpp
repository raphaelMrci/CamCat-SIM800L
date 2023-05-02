#pragma once

#include <string>

#define CAMCAT_VERSION "1.0.0"

// #define NDEBUG

namespace Camcat {
    struct Config {
        public:
            String ssid;
            String password;

            String SIMPinCode;

            String SIMAPN;
            String SIMMMSCURL;
            String SIMMMSPROTO;
    };
} // namespace Camcat

#ifdef NDEBUG
    #define CAMCAT_DEBUG_PRINT(x)
    #define CAMCAT_DEBUG_PRINTLN(x)
#else
    #define CAMCAT_DEBUG_PRINT(x)   Serial.print(x)
    #define CAMCAT_DEBUG_PRINTLN(x) Serial.println(x)
#endif
