#pragma once

#define CAMCAT_VERSION "1.0.0"

#define CAMCAT_SIM800L_RX_PIN (int)10
#define CAMCAT_SIM800L_TX_PIN (int)11

// #define NDEBUG

#ifdef NDEBUG
#define CAMCAT_DEBUG_PRINT(x)
#define CAMCAT_DEBUG_PRINTLN(x)
#else
#define CAMCAT_DEBUG_PRINT(x) Serial.print(x)
#define CAMCAT_DEBUG_PRINTLN(x) Serial.println(x)
#endif
