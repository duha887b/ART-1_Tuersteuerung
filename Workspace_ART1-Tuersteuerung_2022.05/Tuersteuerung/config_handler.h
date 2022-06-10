//
// Created by supertrooper on 07.06.2022.
//

#ifndef CONFIG_HANDLER_HH
#define CONFIG_HANDLER_HH

#include "Aktor.h"
#include "Sensor.h"
#include "HardwareElement.h"

class config_handler {

public:
    std::vector<HardwareElement> run();
    static config_handler& get_instance();
    config_handler();

private:

    //~config_handler();

};

#endif // CONFIG_HANDLER_HH
