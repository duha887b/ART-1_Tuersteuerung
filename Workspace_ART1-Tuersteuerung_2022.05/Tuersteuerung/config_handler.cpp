//
// Created by supertrooper on 07.06.2022.
//

#include "config_handler.h"
#include "HardwareElement.h"
#include <fstream>
#include <iostream>
#include <string>


//config_handler(const config_handler&) = delete;				//nur Referenzierung, keine Kopie möglich
//static config_handler* _instance;

//std::vector<HardwareElement*> aktoren_sensoren_ini;


config_handler::config_handler() {

}

static config_handler& get_instance() {
    //if (_instance==NULL) {
    //	_instance = new config_handler();
    //}
    static config_handler _instance;
    return _instance;
}

//std::vector<HardwareElement*> config_handler::run() {

void config_handler::run() {
    std::string filename = "config.txt";

    std::ifstream input(filename);

   // if (!input) {
   //     std::cerr << "Keine config Datei gefunden";    Fehler für logfile!!!
   //     return NULL;
   // }

    std::string line;
    std::string delimiter = ",";
    std::string token;
    size_t pos = 0;
    std::string aktoren_sensoren_read[24][5];

    int i=0;


    while (std::getline(input, line)) {
        //std::cout << line << "/n";
        //if ((line!="")&&i>23)             Fehler für logfile
        //std::cout << "while(getline)" << std::endl;
        int m=0;

        while((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0,pos);
            //std::cout << "Zeile: " << line << std::endl;
            //std::cout << token << std::endl;
            //aktoren_sensoren_read.at(i).at(m) = token;
            aktoren_sensoren_read[i][m] = token;
            line.erase(0,pos+delimiter.length());
            m++;
            if (m==4) aktoren_sensoren_read[i][m] = line;
            //std::cout << "m: " << m << std::endl;
        }

        i++;
        //std::cout << "i: " << i << std::endl;


    }
    //std::cout << "while(getline) fertig" << std::endl;
    //int port=0;

    for (int j=0;j<24;j++) {              //24 -> 3 Ports mit je 8 pins

        //if (((j+1)%8)==0)  port++;         //für die richtige Portzuweisung

        //sensor aktor initialisierung

        //std::cout << "for Anfang" << std::endl;

        if (aktoren_sensoren_read[j][1]=="reserviert"){
            aktoren_sensoren_ini[j] = new HardwareElement(-1,-1,false);

            continue;
        }

        std::string port_tmp = aktoren_sensoren_read[j][3];
        std::string pin_tmp = aktoren_sensoren_read[j][4];
        std::string opMode_tmp = aktoren_sensoren_read[j][2];

        int i_port_tmp = std::stoi(port_tmp);
        int i_pin_tmp = std::stoi(pin_tmp);
        int i_opMode_tmp = std::stoi(opMode_tmp);

        //if (i_port_tmp>2 || i_port_tmp<0) ; //Fehler für logfile

        if (aktoren_sensoren_read[j][0]=="sensor") {
            //neuen sensor definieren

            aktoren_sensoren_ini[j] = new Sensor(i_port_tmp,i_pin_tmp,0,i_opMode_tmp);

            continue;
        }

        if (aktoren_sensoren_read[j][0]=="aktor") {
            //neuen aktor definieren

            aktoren_sensoren_ini[j] = new Aktor(i_port_tmp,i_pin_tmp,0);

            continue;
        }

        else {       //logfile für Fehler

    }

    }

    std::cout << "cfg wurde eingelesen" << std::endl;


}

Sensor* config_handler::sensoren_get() {
   Sensor sens(1,1, true, true) ;//= new Sensor[16];

    for (int i = 0; i < 16; i++) {
        aktoren_sensoren_ini[i];
        aktoren_sensoren_ini[i]->getPin();
        //std::cout << std::to_string((aktoren_sensoren_ini[i]->getPin()))<<std::endl;
    }


    return &sens;
}
/*
Aktor config_handler::aktoren_get() {
    Aktor *akt[8];

    for(int i=0;i<8;i++) {
        *akt[i] = *aktoren_sensoren_ini[16+i];
    }

    return *akt;

}
*/