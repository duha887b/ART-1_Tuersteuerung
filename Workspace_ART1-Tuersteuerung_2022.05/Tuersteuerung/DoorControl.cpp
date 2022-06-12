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
                             handler()


{
    // constructor
    // ... maybe, insert your sensor and actor initialization here?

    //Temp ini später durch config handler

    handler.run();
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

        // Betriebsmodus auswahl //TODO BW1,2 ansprechen
        //00 Aus
        //10 Handbetrieb
        //01 Reparatur
        //11 Automatik

        //TODO if clause Auswahl der Modi


        //construct counter message
        msg = "press 'q' to quit ";
        msg += std::to_string((int)((delay_ms*tm)/1000));
        msg += " s, timer: ";
        msg += std::to_string((int )(stateTimer/1000));
        msg += "  ";

        for (int i = 0; i < 15; i++) { //reference für debug string
            msg+= std::to_string(handler.sens_list.at(i)->getState());
            }



        //TODO debug an richtige instance
        // set current message to be displayed by user interface
        door_if.DebugString(msg);



        // wait some time
        usleep(delay_ms * 1000);
        stateTimer += delay_ms;
        tm++;
    }
}

void DoorControl::updateHardwareElements(){


//TODO Tobi anpassen der instanzen Harware Element
//TODO if clause HardwareInterface oder Simulatior --> door_if



    if(true) {// bedingung für Simulator

        door_if.DIO_Read(0,&port0);
        door_if.DIO_Read(1,&port1);

    }
    for (int i = 0; i < 15; i++) { // daten port1 auf pin states schreiben
        if (i<8){
            handler.sens_list.at(i)->setState((port0 >> i) & 1);
        }
        if(i>7){
            handler.sens_list.at(i)->setState((port1 >> (i-8)) & 1);
        }

    }
    //TODO in schleife packen funktioniert grad nicht
/*
    for (int i = 0; i < 8; i++) { //set state for actors
        //std::cout << handler.akt_list.at(i)->getState() << std::endl;

        if(0==(handler.akt_list.at(i)->getState())){
            //std::cout << "of" << std::endl;
            port2 &= 0<< i;
        }
        if((handler.akt_list.at(i)->getState())==1){
            port2 |= 1<< i;



        }

    }
    */
    if(0==(handler.akt_list.at(0)->getState())){
        //std::cout << "of" << std::endl;
        port2 &= 0<< 0;
    }
    if((handler.akt_list.at(0)->getState())==1) {
        port2 |= 1 << 0;

    }
    if(0==(handler.akt_list.at(1)->getState())){
        //std::cout << "of" << std::endl;
        port2 &= 0<< 1;
    }
    if((handler.akt_list.at(1)->getState())==1) {
        port2 |= 1 << 1;

    }
    if(0==(handler.akt_list.at(2)->getState())){
        //std::cout << "of" << std::endl;
        port2 &= 0<< 2;
    }
    if((handler.akt_list.at(2)->getState())==1) {
        port2 |= 1 << 2;

    }





    if(true){//TODO bedingung für insatnz
        door_if.DIO_Write(2,port2);

    }




}


//default Autommaten State-Function
//TODO pseudocode übersetzen tobi fehtl

void DoorControl::defaultFunc(){}

// mehrfach verwendete State Functions
void DoorControl::MotorOf(){
    //!Y1,!Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(false);
}

void DoorControl::doorClose(){
    //!Y1,Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(true);
}
void DoorControl::doorOpen(){
    //Y1,!Y2
    handler.akt_list.at(0)->setState(true);
    handler.akt_list.at(1)->setState(false);
}
void DoorControl::d_AktorenOf(){
    //!Y3!Y2!Y1
    handler.akt_list.at(2)->setState(false);
    MotorOf();
}
//mehrfach verwendete Übergangsbedingungen
bool DoorControl::d_ELO(){ // a_Init_Auf,h_Init_Auf
    return handler.sens_list.at(4)->getState(); //ELO
}

bool DoorControl::d_notEloElg(){ //a_Init_öffnen,h_Init_Stop
    return !(handler.sens_list.at(4)->getState()) && !(handler.sens_list.at(6)->getState()) ; //!ELO && !ELG
}

bool DoorControl::d_ELG(){ //a_Init_Zu,h_Init_Zu,a_schliessen_oeffnen
    return handler.sens_list.at(6)->getState();//ELG
}

bool DoorControl::d_NTZ(){
    return handler.sens_list.at(3)->getState(); //NTZ
}

bool DoorControl::d_NTA(){
    return handler.sens_list.at(2)->getState();//NTA
}
bool DoorControl::d_notNtaNtz(){
    return !(handler.sens_list.at(2)->getState()) && !(handler.sens_list.at(3)->getState()); //!NTA&&!NTZ
}

// Automatikbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool DoorControl::a_NtaLasLsvBm(){ // entspricht schließen-->öffnen, Auf-->Auf
    //NTA || LSH || LSV || BM
    return  handler.sens_list.at(2)->getState()||handler.sens_list.at(7)->getState()||
            handler.sens_list.at(8)->getState()||handler.sens_list.at(9)->getState();
}
bool DoorControl::a_Auf_schliessen(){
    unsigned int delay = 3000;
    if (stateTimer>=delay){
        return true;
    }
    //NTZ && (!NTA && !LSA && !LSV && !BM)
    return  handler.sens_list.at(3)->getState()&&(!(handler.sens_list.at(2)->getState())&&
            !(handler.sens_list.at(7)->getState())&& !(handler.sens_list.at(8)->getState())&&
            !(handler.sens_list.at(9)->getState()));
}
//2. State function
void DoorControl::a_enterInit(){
    //!Y1,!Y2,Y3
    MotorOf();
    handler.akt_list.at(2)->setState(true);
    unsigned int delay = 5000;
    usleep(delay * 1000);
    //!Y3
    handler.akt_list.at(2)->setState(true);
}
void DoorControl::a_enterAuf(){
    stateTimer = 0;
    MotorOf();
}
//Handbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool DoorControl::h_Stop_Stop(){
    //(!NTA&&!NTZ)||(NTZ&&NTA)
    return  (!(handler.sens_list.at(2)->getState())&&!(handler.sens_list.at(3)->getState()))
            &&((handler.sens_list.at(2)->getState())&&(handler.sens_list.at(3)->getState()));
}
//Reparaturbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool DoorControl::r_notNTZ(){
    return !(handler.sens_list.at(3)->getState());//!NTZ
}
bool DoorControl::r_Stop_Stop(){
    //NTZ && (NTA || LSH || LSV || BW)
    return  (handler.sens_list.at(3))&&
            (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));
}
bool DoorControl::r_oeffnen_Stop(){
    //!NTZ && !NTA && !LSH && !LSV && !BW
    return !(handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
            !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
            !(handler.sens_list.at(9));
}
bool DoorControl::r_allNotNTZ(){
    //!NTZ && (NTA || LSH || LSV || BW)
    return   !(handler.sens_list.at(3))&&
             (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));

}
bool DoorControl::r_NTZ_notAll(){
    //NTZ && !NTA && !LSH && !LSV && !BW
    return (handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
           !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
           !(handler.sens_list.at(9));
}
//2. State function
void DoorControl::r_schliessen(){
    doorClose();
    //Y3
    handler.akt_list.at(2)->setState(true);
}
void DoorControl::r_oeffnen(){
    doorOpen();
    //Y3
    handler.akt_list.at(2)->setState(true);
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

    trlist_automatik.push_back(&tr0);
    trlist_automatik.push_back(&tr1);
    trlist_automatik.push_back(&tr2);
    trlist_automatik.push_back(&tr3);
    trlist_automatik.push_back(&tr4);
    trlist_automatik.push_back(&tr5);
    trlist_automatik.push_back(&tr6);
    trlist_automatik.push_back(&tr7);
    trlist_automatik.push_back(&tr8);
    trlist_automatik.push_back(tr9);

    Automat auto_Automatik(trlist_automatik,&Init);
    return &auto_Automatik;
}
 /*
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
*/