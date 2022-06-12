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
    //Sensor* sensoren_get();
    //Aktor aktoren_get();
    void run();
    static config_handler& get_instance();
    config_handler();
    Aktor* get_akt_list();
    Sensor* get_sens_list();
    Aktor* akt_list[8];
    Sensor* sens_list[24];

private:

    HardwareElement *aktoren_sensoren_ini[24];
    //~config_handler();

};

#endif // CONFIG_HANDLER_HH
