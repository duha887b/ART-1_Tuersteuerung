//
// Created by dustin on 6/12/22.
//

#include "AutomatFunction.h"

AutomatFunction::AutomatFunction(config_handler handler) : handler(handler){

}

//default Autommaten State-Function
//TODO pseudocode übersetzen tobi fehtl

void AutomatFunction::defaultFunc(){}

// mehrfach verwendete State Functions
void AutomatFunction::MotorOf(){
    //!Y1,!Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(false);
}

void AutomatFunction::doorClose(){
    //!Y1,Y2
    handler.akt_list.at(0)->setState(false);
    handler.akt_list.at(1)->setState(true);
}
void AutomatFunction::doorOpen(){
    //Y1,!Y2
    handler.akt_list.at(0)->setState(true);
    handler.akt_list.at(1)->setState(false);
}
void AutomatFunction::d_AktorenOf(){
    //!Y3!Y2!Y1
    handler.akt_list.at(2)->setState(false);
    MotorOf();
}
//mehrfach verwendete Übergangsbedingungen
bool AutomatFunction::d_ELO(){ // a_Init_Auf,h_Init_Auf
    return handler.sens_list.at(4)->getState(); //ELO
}

bool AutomatFunction::d_notEloElg(){ //a_Init_öffnen,h_Init_Stop
    return !(handler.sens_list.at(4)->getState()) && !(handler.sens_list.at(6)->getState()) ; //!ELO && !ELG
}

bool AutomatFunction::d_ELG(){ //a_Init_Zu,h_Init_Zu,a_schliessen_oeffnen
    return handler.sens_list.at(6)->getState();//ELG
}

bool AutomatFunction::d_NTZ(){
    return handler.sens_list.at(3)->getState(); //NTZ
}

bool AutomatFunction::d_NTA(){
    return handler.sens_list.at(2)->getState();//NTA
}
bool AutomatFunction::d_notNtaNtz(){
    return !(handler.sens_list.at(2)->getState()) && !(handler.sens_list.at(3)->getState()); //!NTA&&!NTZ
}

// Automatikbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool AutomatFunction::a_NtaLasLsvBm(){ // entspricht schließen-->öffnen, Auf-->Auf
    //NTA || LSH || LSV || BM
    return  handler.sens_list.at(2)->getState()||handler.sens_list.at(7)->getState()||
            handler.sens_list.at(8)->getState()||handler.sens_list.at(9)->getState();
}
bool AutomatFunction::a_Auf_schliessen(){
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
void AutomatFunction::a_enterInit(){
    //!Y1,!Y2,Y3
    MotorOf();
    handler.akt_list.at(2)->setState(true);
    unsigned int delay = 5000;
    usleep(delay * 1000);
    //!Y3
    handler.akt_list.at(2)->setState(false);
}
void AutomatFunction::a_enterAuf(){
    stateTimer = 0;
    MotorOf();
}
//Handbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool AutomatFunction::h_Stop_Stop(){
    //(!NTA&&!NTZ)||(NTZ&&NTA)
    return  (!(handler.sens_list.at(2)->getState())&&!(handler.sens_list.at(3)->getState()))
            &&((handler.sens_list.at(2)->getState())&&(handler.sens_list.at(3)->getState()));
}
//Reparaturbetrieb
//1. Zustandsübergangsfunktionen (Betriebsart_startZustand_zielZustand())
bool AutomatFunction::r_notNTZ(){
    return !(handler.sens_list.at(3)->getState());//!NTZ
}
bool AutomatFunction::r_Stop_Stop(){
    //NTZ && (NTA || LSH || LSV || BW)
    return  (handler.sens_list.at(3))&&
            (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));
}
bool AutomatFunction::r_oeffnen_Stop(){
    //!NTZ && !NTA && !LSH && !LSV && !BW
    return !(handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
           !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
           !(handler.sens_list.at(9));
}
bool AutomatFunction::r_allNotNTZ(){
    //!NTZ && (NTA || LSH || LSV || BW)
    return   !(handler.sens_list.at(3))&&
             (handler.sens_list.at(2)||handler.sens_list.at(7)||handler.sens_list.at(8)||handler.sens_list.at(9));

}
bool AutomatFunction::r_NTZ_notAll(){
    //NTZ && !NTA && !LSH && !LSV && !BW
    return (handler.sens_list.at(3))&& !(handler.sens_list.at(2))&&
           !(handler.sens_list.at(7))&& !(handler.sens_list.at(8))&&
           !(handler.sens_list.at(9));
}
//2. State function
void AutomatFunction::r_schliessen(){
    doorClose();
    //Y3
    handler.akt_list.at(2)->setState(true);
}
void AutomatFunction::r_oeffnen(){
    doorOpen();
    //Y3
    handler.akt_list.at(2)->setState(true);
}
