#include "Controller.hpp"

Camcat::Controller::Controller()
{
    _sdReader = new Camcat::SDReader();
    Camcat::Config config = _sdReader->readConfig();

    _network = new Camcat::Network(config.ssid, config.password);
    _sim900 = new Camcat::Sim900(config);
}

Camcat::Controller::~Controller()
{
    delete _network;
    delete _sdReader;
    delete _sim900;
}
