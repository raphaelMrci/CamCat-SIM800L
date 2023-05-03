#include <Arduino.h>
#include <EEPROM.h>
#include "Camcat.hpp"

void setup()
{
    EEPROM.begin(EEPROM_SIZE);
}

void exitProgram()
{
    EEPROM.end();
    CAMCAT_DEBUG_PRINTLN("Exiting program...");
    exit(0);
}

void loop()
{
    // put your main code here, to run repeatedly:
}
