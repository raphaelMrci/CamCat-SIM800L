#pragma once

#include "Camcat.hpp"
#include <SoftwareSerial.h>
#include <memory>
#include <string>

class Sim800L
{
  public:
    Sim800L();
    ~Sim800L();
    void sendATCommand(std::string command);

    void setSMSMode();
    void setSMSFormat();
    void sendSMS(std::string number, std::string text);

    std::string getNumber();
    std::string getText();
    std::string getDate();
    std::string getTime();
    std::string getFullSMS();

  private:
    SoftwareSerial *_serial;
};
