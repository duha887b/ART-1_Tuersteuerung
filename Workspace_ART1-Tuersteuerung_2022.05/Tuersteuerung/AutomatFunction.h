//
// Created by dustin on 6/12/22.
//

#ifndef ART_1_TUERSTEUERUNG_AUTOMATFUNCTION_H
#define ART_1_TUERSTEUERUNG_AUTOMATFUNCTION_H

#include "config_handler.h"

class AutomatFunction {

public:

    AutomatFunction(config_handler handler);
    ~AutomatFunction();

    config_handler handler;

    void defaultFunc();
    void MotorOf();
    void doorClose();
    void doorOpen();
    void d_AktorenOf();

    bool d_ELO();
    bool d_notEloElg();
    bool d_ELG();
    bool d_NTZ();
    bool d_NTA();
    bool d_notNtaNtz();

    bool a_NtaLasLsvBm();
    bool a_Auf_schliessen();

    void a_enterInit();
    void a_enterAuf();

    bool h_Stop_Stop();

    bool r_notNTZ();
    bool r_Stop_Stop();
    bool r_oeffnen_Stop();
    bool r_allNotNTZ();
    bool r_NTZ_notAll();

    void r_schliessen();
    void r_oeffnen();

};


#endif //ART_1_TUERSTEUERUNG_AUTOMATFUNCTION_H
