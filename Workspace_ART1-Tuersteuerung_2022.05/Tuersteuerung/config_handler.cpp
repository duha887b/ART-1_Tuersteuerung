//
// Created by supertrooper on 07.06.2022.
//

#include "config_handler.h"
#include <fstream>
#include <iostream>
#include <string>

//config_handler(const config_handler&) = delete;				//nur Referenzierung, keine Kopie möglich
//static config_handler* _instance;

std::vector<std::vector> actuators_sensors;

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
        actuators_sensors.at(i);
        i=++;
    }

    for (j=0;j<i-1;j++) {
        //sensor aktor initialisierung

    }

}
