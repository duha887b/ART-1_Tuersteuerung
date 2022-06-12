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
    std::vector<Aktor*> get_akt_list();
    std::vector<Sensor*> get_sens_list();
    std::vector<Aktor*> akt_list;
    std::vector<Sensor*> sens_list;

private:

    HardwareElement *aktoren_sensoren_ini[24];
    //~config_handler();

};

#endif // CONFIG_HANDLER_HH
