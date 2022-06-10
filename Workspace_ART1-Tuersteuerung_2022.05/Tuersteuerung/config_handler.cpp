//
// Created by supertrooper on 07.06.2022.
//

#include "config_handler.h"
#include "HardwareElement.h"
#include "Sensor.h"
#include "Aktor.h"
#include <fstream>
#include <iostream>
#include <string>

//config_handler(const config_handler&) = delete;				//nur Referenzierung, keine Kopie möglich
//static config_handler* _instance;

std::vector<HardwareElement> aktoren_sensoren_ini;

config_handler::config_handler() {

}

static config_handler& get_instance() {
    //if (_instance==NULL) {
    //	_instance = new config_handler();
    //}
    static config_handler _instance;
    return _instance;
}

std::vector<HardwareElement> config_handler::run() {

    std::string filename = "config.txt";

    std::ifstream input(filename);

    if (!input) {
        std::cerr << "Keine config Datei gefunden";
        return;
    }

    std::string line;
    std::vector_tmp<std::string>;
    std::vector<std::vector> aktoren_sensoren_read;

    i=0;

    while (std::getline(input, line)) {
        //std::cout << line << "/n";
       // if ((line!="")&&i>23)             Fehler für logfile

        vector_tmp=split(line);
        aktoren_sensoren_read.at(i)=vector_tmp;
        i++;
    }

    int port=0;

    for (j=0;j<24;j++) {              //24 -> 3 Ports mit je 8 pins

        //if (((j+1)%8)==0)  port++;         //für die richtige Portzuweisung

        //sensor aktor initialisierung
        if (aktoren_sensoren_read.at(j).at(0)=="reserviert"){
            aktoren_sensoren_ini.at(j) = new HardwareElement(-1,-1,0);

            continue;
        }

        std::string port_tmp = aktoren_sensoren_read.at(j).at(3);
        std::string pin_tmp = aktoren_sensoren_read.at(j).at(4);
        std::string opMode_tmp = aktoren_sensoren_read.at(j).at(2);

        int i_port_tmp = std::stoi(port_tmp);
        int i_pin_tmp = std::stoi(pin_tmp);
        int i_opMode_tmp = std::stoi(opMode_tmp);

        //if (i_port_tmp>2 || i_port_tmp<0) ; //Fehler für logfile

        if (aktoren_sensoren_read_sensoren_read.at(j).at(0)=="sensor") {
            //neuen sensor definieren

            aktoren_sensoren_ini.at(j) = new Sensor(i_port_tmp,i_pin_tmp,0,i_opMode_tmp);

            continue;
        }

        if (aktoren_sensoren_read.at(j).at(0)=="aktor") {
            //neuen aktor definieren

            aktoren_sensoren_ini.at(j) = new Aktor(i_port_tmp,i_pin_tmp,0);

            continue;
        }
        else {       //logfile für Fehler
    }

    }

    return aktoren_sensoren_ini;

}
