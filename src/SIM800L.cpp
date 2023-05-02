#include "SIM800L.hpp"
#include "Camcat.hpp"

Sim800L::Sim800L()
{
    _serial = new SoftwareSerial(CAMCAT_SIM800L_TX_PIN, CAMCAT_SIM800L_RX_PIN);
    _serial->begin(9600);

    sendATCommand("AT");
    sendATCommand("AT+CMGF=1");
}

Sim800L::~Sim800L()
{
    delete _serial;
}

void Sim800L::sendATCommand(std::string command)
{
    _serial->println(command.c_str());
}
