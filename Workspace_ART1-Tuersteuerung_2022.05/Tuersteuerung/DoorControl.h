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
#include "AutomatFunction.h"
#include "HardwareInterface.h"
#include "UserInterface.h"



class DoorControl {
public:
    DoorControl();
    ~DoorControl();
    void run();
private:

    void updateHardwareElements();

    Simulator door_if;
    HardwareInterface door_real;
    UserInterface ui;

    config_handler handler;


    unsigned char opMode;
    unsigned char port0;
    unsigned char port1;
    unsigned char port2 = 0;

    Automat* handbetrieb;
    Automat* reparatur;
    Automat* automatik ;

    void iniHandbetrieb();
    void iniReparaturmodus();
    void iniAutomatik();

    std::list<Transition*>trlist_handbetrieb;
    std::list<Transition*>trlist_reparatur;
    std::list<Transition*>trlist_automatik;

   // AutomatFunction AutoFunction;

    //automatik guardfunction
};


#endif // DOORCONTROL_HH