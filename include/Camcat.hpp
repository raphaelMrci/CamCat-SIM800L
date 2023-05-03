#pragma once

#include <Arduino.h>
#include <string>

#define CAMCAT_VERSION "1.0.0"

/* Pin definition for CAMERA_MODEL_AI_THINKER */
#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27

#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM    5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

/* SERIAL2 RX/TX */
#define CAMCAT_SIM800L_TX_PIN 4
#define CAMCAT_SIM800L_RX_PIN 5

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
    #define CAMCAT_DEBUG_PRINTF(x, ...)
#else
    #define CAMCAT_DEBUG_PRINT(x)       Serial.print(x)
    #define CAMCAT_DEBUG_PRINTLN(x)     Serial.println(x)
    #define CAMCAT_DEBUG_PRINTF(x, ...) Serial.printf(x, __VA_ARGS__)
#endif
