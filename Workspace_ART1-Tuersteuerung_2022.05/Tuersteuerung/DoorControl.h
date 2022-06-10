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


class DoorControl {
public:
	DoorControl();
	~DoorControl();
	void run();
private:

    void updateHardwareElements();
    void iniHandbetrieb();
    void iniReperatur();
    void iniAutomatik();
    void switchStepAutomat();
    void stepHandbetrieb();
    void stepReperatur();
    void stepAutomatik();
    void turnOff();

	Simulator door_if;
    Sensor BW1;
    Sensor BW2;
    Sensor NTA;
    Sensor NTZ;
    Sensor ELO;
    Sensor res;
    Sensor ELG;
    Sensor LSH;

    Sensor LSV;
    Sensor BM;

    Aktor Y1;
    Aktor Y2;
    Aktor Y3;

    unsigned char opMode;
    unsigned char port0;
    unsigned char port1;
    unsigned char port2 = 0;

};


#endif // DOORCONTROL_HH
