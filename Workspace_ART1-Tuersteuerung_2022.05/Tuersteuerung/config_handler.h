//
// Created by supertrooper on 07.06.2022.
//

#ifndef CONFIG_HANDLER_HH
#define CONFIG_HANDLER_HH

#include "Aktor.h"
#include "Sensor.h"
#include "HardwareElement.h"
#include <vector>

class config_handler {

public:
    Sensor sensoren_get();
    Aktor aktoren_get();
    HardwareElement* run();
    static config_handler& get_instance();
    config_handler();

private:

    //~config_handler();

};

#endif // CONFIG_HANDLER_HH
