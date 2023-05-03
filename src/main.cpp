#include <Arduino.h>
#include <EEPROM.h>
#include "Camcat.hpp"
#include "CameraController.hpp"
#include "SDReader.hpp"
#include "SIM900.hpp"

void setup()
{
    Serial.begin(115200);
    CAMCAT_DEBUG_PRINTLN("Starting program...");
    CAMCAT_DEBUG_PRINTLN("Initializing EEPROM...");
    EEPROM.begin(EEPROM_SIZE);
    CAMCAT_DEBUG_PRINTLN("Initializing EEPROM... Done!");
    CAMCAT_DEBUG_PRINTLN("Initializing Camera...");
    Camcat::CameraController cameraController;
    CAMCAT_DEBUG_PRINTLN("Initializing Camera... Done!");
    CAMCAT_DEBUG_PRINTLN("Initializing SD Card...");
    Camcat::SDReader sdReader;
    CAMCAT_DEBUG_PRINTLN("Initializing SD Card... Done!");
    CAMCAT_DEBUG_PRINTLN("Reading config...");
    Camcat::Config config = sdReader.readConfig();
    CAMCAT_DEBUG_PRINTLN("Reading config... Done!");
    CAMCAT_DEBUG_PRINTLN("Initializing SIM900...");
    Camcat::Sim900 sim900(config);
    CAMCAT_DEBUG_PRINTLN("Initializing SIM900... Done!");

#ifdef CAMCAT_DEBUG_MODE
    sim900.sendSMS("Camcat started");
#endif
}

void exitProgram()
{
    EEPROM.end();
    CAMCAT_DEBUG_PRINTLN("Exiting program...");
    exit(0);
}

void loop()
{
}
