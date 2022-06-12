/*  -*- mode: c++; -*-
 * Praktikum MRT2
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r3
 */
#ifndef DOORCONTROL_HH
#define DOORCONTROL_HH

#include "ncurses.h"
#include "Simulator.h"
#include "Sensor.h"
#include "Aktor.h"
#include "Automat.h"
#include "State.h"
#include "Transition.h"
#include <iostream>
#include "config_handler.h"
#include <vector>



class DoorControl {
public:
    DoorControl();
    ~DoorControl();
    void run();
private:

    void updateHardwareElements();
    Simulator door_if;
    config_handler handler;


    unsigned char opMode;
    unsigned char port0;
    unsigned char port1;
    unsigned char port2 = 0;

    unsigned int stateTimer; // in ms


/*
    Automat handbetrieb;
    Automat reparatur;
    Automat automatik;
*/
    Automat* iniHandbetrieb();
    Automat* iniReparaturmodus();
    Automat* iniAutomatik();

    std::list<Transition*>trlist_handbetrieb;
    std::list<Transition*>trlist_reperatur;
    std::list<Transition*>trlist_automatik;

    //automatik guardfunction

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


#endif // DOORCONTROL_HH