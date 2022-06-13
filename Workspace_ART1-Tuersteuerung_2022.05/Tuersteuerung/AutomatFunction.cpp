//
// Created by dustin on 6/12/22.
//

#include "AutomatFunction.h"
#include <usb.h>
#include <iostream>
/*
AutomatFunction::AutomatFunction(config_handler handler) : handler(handler){

    stateTimer = 0;

}
*/
//default Autommaten State-Function
//TODO pseudocode übersetzen tobi fehtl

config_handler handler;


unsigned int stateT = 0;


void getHandler(config_handler hl){
    handler = hl;
   /* while (true) {
        std::cout << hl.sens_list.at(0)->getState() << std::endl;
    }*/
}

void stepTimer(unsigned int delay_ms) {
    stateT += delay_ms;
}

void defaultFunc(){}

// mehrfach verwendete State Functions
void MotorOf(){
    //!Y1,!Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(false);
}

void doorClose(){
    //!Y1,Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(true);
}
void doorOpen(){
    //Y1,!Y2

    while (true) {
        std::cout << 32 << std::endl;
    }

    handler.akt_list.at(0)->setState(true);
    handler.akt_list.at(1)->setState(false);
}
void d_AktorenOf(){
    //!Y3!Y2!Y1
    handler.akt_list.at(2)->setState(false);
    MotorOf();
}
//mehrfach verwendete Übergangsbedingungen
bool d_ELO(){ // a_Init_Auf,h_Init_Auf
    return handler.sens_list.at(4)->getState(); //ELO
}

bool d_notEloElg(){ //a_Init_öffnen,h_Init_Stop


    return !(handler.sens_list.at(4)->getState()) && !(handler.sens_list.at(6)->getState()) ; //!ELO && !ELG
}

bool d_ELG(){ //a_Init_Zu,h_Init_Zu,a_schliessen_oeffnen

    return handler.sens_list.at(6)->getState();//ELG
}

bool d_NTZ(){
    return handler.sens_list.at(3)->getState(); //NTZ
}

bool d_NTA(){
    return handler.sens_list.at(2)->getState();//NTA
}
bool d_notNtaNtz(){
    return !(handler.sens_list.at(2)->getState()) && !(handler.sens_list.at(3)->getState()); //!NTA&&!NTZ
}

// Automatikbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool a_NtaLasLsvBm(){ // entspricht schließen-->öffnen, Auf-->Auf
    //NTA || LSH || LSV || BM
    return  handler.sens_list.at(2)->getState()||handler.sens_list.at(7)->getState()||
            handler.sens_list.at(8)->getState()||handler.sens_list.at(9)->getState();
}
bool a_Auf_schliessen(){
    unsigned int delay = 3000;
    if (stateT>=delay){
        return true;
    }
    //NTZ && (!NTA && !LSA && !LSV && !BM)
    return  handler.sens_list.at(3)->getState()&&(!(handler.sens_list.at(2)->getState())&&
                                                  !(handler.sens_list.at(7)->getState())&& !(handler.sens_list.at(8)->getState())&&
                                                  !(handler.sens_list.at(9)->getState()));
}

//2. State function
void a_enterInit(){
    //!Y1,!Y2,Y3
    MotorOf();
    handler.akt_list.at(2)->setState(true);
    /*unsigned int delay = 5000;
    usleep(delay * 1000);
    //!Y3
    handler.akt_list.at(2)->setState(false);*/
}

void a_enterAuf(){
    stateT = 0;
    MotorOf();
}
//Handbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool h_Stop_Stop(){
    //(!NTA&&!NTZ)||(NTZ&&NTA)
    return  (!(handler.sens_list.at(2)->getState())&&!(handler.sens_list.at(3)->getState()))
            &&((handler.sens_list.at(2)->getState())&&(handler.sens_list.at(3)->getState()));
}
//Reparaturbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool r_notNTZ(){
    return !(handler.sens_list.at(3)->getState());//!NTZ
}
bool r_Stop_Stop(){
    //NTZ && (NTA || LSH || LSV || BW)
    return  (handler.sens_list.at(3))&&
            (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));
}
bool r_oeffnen_Stop(){
    //!NTZ && !NTA && !LSH && !LSV && !BW
    return !(handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
           !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
           !(handler.sens_list.at(9));
}
bool r_allNotNTZ(){
    //!NTZ && (NTA || LSH || LSV || BW)
    return   !(handler.sens_list.at(3))&&
             (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));

}
bool r_NTZ_notAll(){
    //NTZ && !NTA && !LSH && !LSV && !BW
    return (handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
           !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
           !(handler.sens_list.at(9));
}
//2. State function
void r_schliessen(){
    doorClose();
    //Y3
    handler.akt_list.at(2)->setState(true);
}
void r_oeffnen(){
    doorOpen();
    //Y3
    handler.akt_list.at(2)->setState(true);
}
