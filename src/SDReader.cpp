#include "SDReader.hpp"
#include <ArduinoJson.h>
#include <dirent.h>
#include "SD_MMC.h"

Camcat::SDReader::SDReader()
{
    if (!SD_MMC.begin("", true)) {
        CAMCAT_DEBUG_PRINTLN("Failed to mount card");
        return;
    }
    CAMCAT_DEBUG_PRINTLN("SD card initialized");

    // Check if config.json file exists in SD card
    if (!SD_MMC.exists("/config.json")) {
        CAMCAT_DEBUG_PRINTLN("Config file not found");

        // Create config.json file
        File file = SD_MMC.open("/config.json", FILE_WRITE);
        if (!file) {
            CAMCAT_DEBUG_PRINTLN("Failed to create config file");
            return;
        }
        file.print(_defaultConfig.c_str());
        file.close();
        CAMCAT_DEBUG_PRINTLN("Config file created");
    }
}

Camcat::Config Camcat::SDReader::readConfig()
{
    String configJson = readFile("/config.json");
    DynamicJsonDocument _jsonDocument(configJson.length() * 2);
    DeserializationError error = deserializeJson(_jsonDocument, configJson);
    Camcat::Config config;

    if (error) {
        CAMCAT_DEBUG_PRINTLN("Failed to read config file");
        return config;
    }
    if (!_jsonDocument["ssid"].is<String>()
    || !_jsonDocument["password"].is<String>()) {
        CAMCAT_DEBUG_PRINTLN("Missing or incorrect SSID or Password");
        return config;
    }
    config.ssid = _jsonDocument["ssid"].as<String>();
    config.password = _jsonDocument["password"].as<String>();

    if (_jsonDocument["apn"].is<String>())
        config.SIMAPN = _jsonDocument["apn"].as<String>();
    else
        CAMCAT_DEBUG_PRINTLN("Missing APN");

    if (_jsonDocument["mmsc_url"].is<String>())
        config.SIMMMSCURL = _jsonDocument["mmsc_url"].as<String>();
    else
        CAMCAT_DEBUG_PRINTLN("Missing MMSC URL");

    if (_jsonDocument["mmsc_proxy"].is<int>())
        config.SIMMMSPROTO = _jsonDocument["mmsc_proto"].as<String>();
    else
        CAMCAT_DEBUG_PRINTLN("Missing MMSC Proxy");
    if (_jsonDocument["pin_code"].is<int>())
        config.SIMPinCode = _jsonDocument["pin_code"].as<String>();
    else
        CAMCAT_DEBUG_PRINTLN("Missing PIN code");
    return config;
}

String Camcat::SDReader::readFile(String path)
{
    File file = SD_MMC.open(path, FILE_READ);
    String reading;

    if (!file) {
        CAMCAT_DEBUG_PRINTLN("Opening file failed");
    }
    reading = file.readString();
    file.close();
    return reading;
}
