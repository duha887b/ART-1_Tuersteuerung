/*
 * Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r2
 */


#include <usb.h>
#include "DoorControl.h"
#include "Sensor.h"
#include "Aktor.h"
#include "Simulator.h"
#include "Automat.h"
#include "State.h"
#include "Transition.h"




DoorControl::DoorControl() : door_if( true) ,
                            opMode(0),
                            BW1(0,0, false,false),
                            BW2(0,1, false,true),
                            NTA(0,2, false,true),
                            NTZ(0,3, false,true),
                            ELO(0,4, false,true),
                            res(0,5, false,true),
                            ELG(0,6, false,true),
                            LSH(0,7, false,true),

                            LSV(1,0, false,true),
                            BM(1,1, false,true),

                            Y1(2,0, false),
                            Y2(2,1, false),
                            Y3(2,2, false)

{
	// constructor
	// ... maybe, insert your sensor and actor initialization here?

    //Temp ini später durch config handler


    stateTimer = 0;



}

DoorControl::~DoorControl()
{
	// destructor
	door_if.quit_simulator_flag = true;
}


void DoorControl::run()
{
	// ... insert your main loop here ...
	// example:






	std::string msg;		// temporary variable to construct message
	unsigned max_count = 20000;	// loop this often
	unsigned delay_ms = 20;		// Milliseconds to wait on one loop
    unsigned int tm = 0;

    while (!door_if.quit_simulator_flag){


        updateHardwareElements();

		//construct counter message
		msg = "press 'q' to quit ";
		msg += std::to_string((int)((delay_ms*tm)/1000));
		msg += " seconds ";

        msg+= std::to_string(BW1.getState());
        msg+= std::to_string(BW2.getState());
        msg+= std::to_string(NTA.getState());
        msg+= std::to_string(NTZ.getState());
        msg+= std::to_string(ELO.getState());
        msg+= std::to_string(res.getState());
        msg+= std::to_string(ELG.getState());
        msg+= std::to_string(LSH.getState());
        msg+= std::to_string(LSV.getState());
        msg+= std::to_string(BM.getState());

		// set current message to be displayed by user interface
		door_if.DebugString(msg);



		// wait some time
		usleep(delay_ms * 1000);
        tm++;
	}
}

void DoorControl::updateHardwareElements(){




    door_if.DIO_Read(0,&port0);
    door_if.DIO_Read(1,&port1);


    BW1.setState((port0 >> 0)&1);
    BW2.setState((port0 >> 1)&1);
    NTA.setState((port0 >> 2)&1);
    NTZ.setState((port0 >> 3)&1);
    ELO.setState((port0 >> 4)&1);
    res.setState((port0 >> 5)&1);
    ELG.setState((port0 >> 6)&1);
    LSH.setState((port0 >> 7)&1);

    LSV.setState((port1 >> 0)&1);
    BM.setState((port1 >> 1)&1);

    //tets


    if(Y1.getState()){
        port2 |= 1<< Y1.getPin();
    } else {
        port2 &= 0<< Y1.getPin();
    }

    if(Y2.getState()){
        port2 |= 1<< Y2.getPin();
    } else {
        port2 &= 0<< Y2.getPin();
    }

    if(Y3.getState()){
        port2 |= 1<< Y3.getPin();
    } else {
        port2 &= 0<< Y3.getPin();
    }

    door_if.DIO_Write(2,port2);

}



//default Autommaten State-Function

void DoorControl::defaultFunc(){}

// mehrfach verwendete State Functions

void DoorControl::MotorOf(){
    //!Y1,!Y2
}
}

void DoorControl::doorClose(){
    //!Y1,Y2
}

void DoorControl::doorOpen(){
    //Y1,!Y2

}

void DoorControl::d_AktorenOf(){
    //!Y3
    MotorOf();
}

//mehrfach verwendete Übergangsbedingungen
bool DoorControl::d_ELO(){ // a_Init_Auf,h_Init_Auf
    return ; //ELO
}
bool DoorControl::d_notEloElg(){ //a_Init_öffnen,h_Init_Stop
    return ; //!ELO && !ELG
}
bool DoorControl::d_ELG(){ //a_Init_Zu,h_Init_Zu,a_schliessen_oeffnen
    return ;//ELG
}
bool DoorControl::d_NTZ(){
    return ; //NTZ
}
bool DoorControl::d_NTA(){
    return ;//NTA
}
bool DoorControl::d_notNtaNtz(){
    return; //!NTA&&!NTZ
}
// Automatikbetrieb

//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())

bool DoorControl::a_NtaLasLsvBm(){ // entspricht schließen-->öffnen, Auf-->Auf
    return ; //NTA || LSA || LSV || BM
}

bool DoorControl::a_Auf_schliessen(){
    unsigned int delay = 3000;
    if (stateTimer>=delay){
        return true;
    }

    return ; //NTZ && (!NTA && !LSA && !LSV && !BM)

}

//2. State function

void DoorControl::a_enterInit(){
    //!Y1,!Y2,Y3
    unsigned int delay = 5000;
    usleep(delay * 1000)
    //!Y3
}

void DoorControl::a_enterAuf(){
    stateTimer = 0;
    MotorOf();

}

//Handbetrieb

//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())

bool DoorControl::h_Stop_Stop(){
    return ;//(!NTA&&!NTZ)||(NTZ&&NTA)
}

//Reparaturbetrieb

//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())

bool DoorControl::r_notNTZ(){
    return ;//!NTZ
}

bool DoorControl::r_Stop_Stop(){
    return ;//NTZ && (NTA || LSH || LSV || BW)
}

bool DoorControl::r_oeffnen_Stop(){
    return ;//!NTZ && !NTA && !LSH && !LSV && !BW
}

bool DoorControl::r_allNotNTZ(){
    return ;//!NTZ && (NTA || LSH || LSV || BW)
}

bool DoorControl::r_NTZ_notAll(){
    return ;//NTZ && !NTA && !LSH && !LSV && !BW
}

//2. State function

void DoorControl::r_schliessen(){
    doorClose();
    //Y3
}

void DoorControl::r_oeffnen(){
    doorOpen();
    //Y3
}

Automat* DoorControl::iniAutomatik() {
    State Init(&a_enterInit,&MotorOf,&defaultFunc);
    State Zu(&MotorOf,&MotorOf,&defaultFunc);
    State Auf(&MotorOf,&MotorOf,&defaultFunc);
    State Oeffnen(&doorOpen,&doorOpen,&defaultFunc);
    State Schliessen(&doorClose,&doorClose,&defaultFunc);

    Transition tr0(&Init,&Zu,&d_ELG);
    Transition tr1(&Init,&Oeffnen,&d_notEloElg);
    Transition tr2(&Init,&Auf,&d_ELO);
    Transition tr3(&Auf,&Auf,&a_NtaLasLsvBm);
    Transition tr4(&Auf,&Schliessen,&a_Auf_schliessen);
    Transition tr5(&Oeffnen,&Auf,&d_ELO);
    Transition tr6(&Oeffnen,&Schliessen,&d_NTZ);
    Transition tr7(&Schliessen,&Zu,&d_ELG);
    Transition tr8(&Schliessen,&Oeffnen,&a_NtaLasLsvBm);
    Transition tr9(&Zu,&Oeffnen,&a_NtaLasLsvBm);

    trlist_automatik.push_back(tr0);
    trlist_automatik.push_back(tr1);
    trlist_automatik.push_back(tr2);
    trlist_automatik.push_back(tr3);
    trlist_automatik.push_back(tr4);
    trlist_automatik.push_back(tr5);
    trlist_automatik.push_back(tr6);
    trlist_automatik.push_back(tr7);
    trlist_automatik.push_back(tr8);
    trlist_automatik.push_back(tr9);

    Automat auto_Automatik(trlist_automatik,&Init);

    return &auto_Automatik;

}
Automat* DoorControl::iniHandbetrieb() {
    State Init(&d_AktorenOf,&d_AktorenOf,&defaultFunc);
    State Zu(&MotorOf,&MotorOf,&defaultFunc);
    State Auf(&MotorOf,&MotorOf,&defaultFunc);
    State Oeffnen(&doorOpen,&doorOpen,&defaultFunc);
    State Schliessen(&doorClose,&doorClose,&defaultFunc);
    State Stop(&MotorOf,&MotorOf,&defaultFunc);

    Transition tr0(&Init,&Zu,&d_ELG);
    Transition tr1(&Init,&Auf,&d_ELO);
    Transition tr2(&Init,&Stop,&d_notEloElg);
    Transition tr3(&Zu,&Oeffnen,&d_NTA);
    Transition tr4(&Oeffnen,&Auf,&d_ELO);
    Transition tr5(&Oeffnen,&Stop,&d_notNtaNtz);
    Transition tr6(&Oeffnen,&Oeffnen,&d_NTA);
    Transition tr7(&Oeffnen,&Schliessen,&d_NTZ);
    Transition tr8(&Schliessen,&Oeffnen,&d_NTA);
    Transition tr9(&Schliessen,&Schliessen,&d_NTZ);
    Transition tr10(&Schliessen,&Zu,&d_ELG);
    Transition tr12(&Schliessen,&Stop,&d_notNtaNtz);
    Transition tr11(&Auf,&Schliessen,&d_NTZ);
    Transition tr13(&Stop,&Schliessen,&d_NTZ);
    Transition tr14(&Stop,&Oeffnen,&d_NTA);
    Transition tr15(&Stop,&Stop,&h_Stop_Stop);


    trlist_handbetrieb.push_back(tr0);
    trlist_handbetrieb.push_back(tr1);
    trlist_handbetrieb.push_back(tr2);
    trlist_handbetrieb.push_back(tr3);
    trlist_handbetrieb.push_back(tr4);
    trlist_handbetrieb.push_back(tr5);
    trlist_handbetrieb.push_back(tr6);
    trlist_handbetrieb.push_back(tr7);
    trlist_handbetrieb.push_back(tr8);
    trlist_handbetrieb.push_back(tr9);
    trlist_handbetrieb.push_back(tr10);
    trlist_handbetrieb.push_back(tr11);
    trlist_handbetrieb.push_back(tr12);
    trlist_handbetrieb.push_back(tr13);
    trlist_handbetrieb.push_back(tr14);
    trlist_handbetrieb.push_back(tr15);


    Automat auto_Handbetrieb(trlist_handbetrieb,&Init);

    return &auto_Handbetrieb;
}
Automat* DoorControl::iniReparaturmodus() {
    State Init(&d_AktorenOf,&d_AktorenOf,&defaultFunc);
    State Zu(&d_AktorenOf,&d_AktorenOf,&defaultFunc);
    State Auf(&d_AktorenOf,&d_AktorenOf,&defaultFunc);
    State Oeffnen(&r_oeffnen,&r_oeffnen,&defaultFunc);
    State Schliessen(&r_schliessen,&r_schliessen,&defaultFunc);
    State Stop(&d_AktorenOf,&d_AktorenOf,&defaultFunc);

    Transition tr0(&Init,&Stop,&d_notEloElg);
    Transition tr2(&Init,&Auf,&d_ELO);
    Transition tr3(&Init,&Zu,&d_ELG);
    Transition tr4(&Stop,&Schliessen,&r_NTZ_notAll);
    Transition tr5(&Stop,&Stop,&r_Stop_Stop);
    Transition tr6(&Oeffnen,&Stop,&r_oeffnen_Stop);
    Transition tr7(&Oeffnen,&Schliessen,&r_NTZ_notAll);
    Transition tr8(&Oeffnen,&Auf,&d_ELO);
    Transition tr9(&Auf,&Schliessen,&r_NTZ_notAll);
    Transition tr10(&Schliessen,&Zu,&d_ELG);
    Transition tr11(&Schliessen,&Oeffnen,&r_allNotNTZ);
    Transition tr12(&Schliessen,&Stop,&r_notNTZ);
    Transition tr13(&Stop,&Stop,&r_Stop_Stop);

    trlist_reperatur.push_back(tr0);
    trlist_reperatur.push_back(tr1);
    trlist_reperatur.push_back(tr2);
    trlist_reperatur.push_back(tr3);
    trlist_reperatur.push_back(tr4);
    trlist_reperatur.push_back(tr5);
    trlist_reperatur.push_back(tr6);
    trlist_reperatur.push_back(tr7);
    trlist_reperatur.push_back(tr8);
    trlist_reperatur.push_back(tr9);
    trlist_reperatur.push_back(tr10);
    trlist_reperatur.push_back(tr11);
    trlist_reperatur.push_back(tr12);
    trlist_reperatur.push_back(tr13);

    Automat auto_Reperaturmodus(trlist_reperatur,&Init);
}
