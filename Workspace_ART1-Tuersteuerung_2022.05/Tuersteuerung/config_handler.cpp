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

std::vector<std::vector> aktoren_sensoren_read;
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

void config_handler::run() {

    std::string filename = "config.txt";

    std::ifstream input(filename);

    if (!input) {
        std::cerr << "Keine config Datei gefunden";
        return;
    }

    std::string line;
    std::vector_tmp<std::string>;
    i=0;

    while (std::getline(input, line)) {
        //std::cout << line << "/n";
        vector_tmp=split(line);
        aktoren_sensoren_read.at(i);
        i=++;
    }

    for (j=0;j<i-1;j++) {
        //sensor aktor initialisierung
        if (aktoren_sensoren_read_sensoren_read.at(j).at(0)=="sensor") {
            //neuen sensor definieren
        }
        if (aktoren_sensoren_read.at(j).at(0)=="aktor") {
            //neuen aktor definieren
        }
        else (//logfile für Fehler) {
    }


    }

}
