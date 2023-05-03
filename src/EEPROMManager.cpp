#include "EEPROMManager.hpp"
#include <EEPROM.h>

void Camcat::EEPROMManager::writeString(int addrOffset, String data)
{
    int strLen = data.length();

    for (int i = 0; i < strLen; i++) {
        EEPROM.write(addrOffset + i, data[i]);
    }
    EEPROM.write(addrOffset + strLen, '\0');
    EEPROM.commit();
}

String Camcat::EEPROMManager::readString(int addrOffset)
{
    String data = "";
    char c = EEPROM.read(addrOffset);
    int i = 0;

    while (c != '\0') {
        data += c;
        c = EEPROM.read(addrOffset + ++i);
    }

    return data;
}

void Camcat::EEPROMManager::writeInt(int addrOffset, int data)
{
    EEPROM.write(addrOffset, data);
    EEPROM.commit();
}

int Camcat::EEPROMManager::readInt(int addrOffset)
{
    return EEPROM.read(addrOffset);
}
