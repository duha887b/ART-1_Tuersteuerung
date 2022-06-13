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
#include <vector>
#include <map>
#include "AutomatFunction.h"



DoorControl::DoorControl() : door_if(true) ,
                             opMode(0),
                             handler(),
                             automatik(),
                             handbetrieb(),
                             reparatur(),
                             ui(),
                             door_real()

                             //AutoFunction(handler)

{
    // constructor
    // ... maybe, insert your sensor and actor initialization here?

    //Temp ini später durch config handle
    handler.run();
    getHandler(handler);
    door_real.quit_hardware_flag=true;
    ui.quit_ui_flag=true;
    door_if.quit_simulator_flag=false;



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

    if (!door_real.quit_hardware_flag){
        door_real.startInterface();
    }

    std::string msg;		// temporary variable to construct message
    unsigned max_count = 20000;	// loop this often
    unsigned delay_ms = 20;		// Milliseconds to wait on one loop
    unsigned int tm = 0;
    //automatik.step();
    iniAutomatik();
    iniHandbetrieb();
    iniReparaturmodus();
    int a=0,h=0,r=0;

    while ((!door_if.quit_simulator_flag && door_real.quit_hardware_flag) || (door_if.quit_simulator_flag && !door_real.quit_hardware_flag)){

        updateHardwareElements();

        // Betriebsmodus auswahl //TODO BW1,2 ansprechen
        //00 Aus
        //10 Handbetrieb
        //01 Reparatur
        //11 Automatik

        int BW1 = handler.sens_list.at(0)->getState();
        int BW2 = handler.sens_list.at(1)->getState();


        if (BW1&&BW2) {
            if (h==1 || r==1) {
                automatik->restartAutomat();
                r=0;
                h=0;
            }
            if (a==0) {
                handler.akt_list.at(2)->setState(true);
                updateHardwareElements();
                usleep(5000*1000); //5s
                handler.akt_list.at(2)->setState(false);
                updateHardwareElements();
            }
            a=1;
            automatik->step();
        }
        else if (BW1&&!BW2) {
            if (a==1 || r==1) {
                handbetrieb->restartAutomat();
                a=0;
                r=0;
            }
            h=1;
            handbetrieb->step();
        }
        else if (!BW1&&BW2) {
            if (a==1 || h==1) {
                reparatur->restartAutomat();
                a=0;
                h=0;
            }
            r=1;
            reparatur->step();
        }
        else if (!BW1&&!BW2) {
            d_AktorenOf();
        }

        //TODO if clause Auswahl der Modi


        //construct counter message

        msg = automatik->getState();
        msg += "press 'q' to quit ";
        msg += std::to_string((int)((delay_ms*tm)/1000));
        msg += " s, timer: ";


        for (int i = 0; i < 15; i++) { //reference für debug string
            msg+= std::to_string(handler.sens_list.at(i)->getState());
            }



        //TODO debug an richtige instance
        // set current message to be displayed by user interface
        door_if.DebugString(msg);



        // wait some time
        usleep(delay_ms * 1000);

        stepTimer(delay_ms);

        tm++;
    }
}

void DoorControl::updateHardwareElements(){


//TODO if clause HardwareInterface oder Simulatior --> door_if



    if(!door_if.quit_simulator_flag) {// bedingung für Simulator

        door_if.DIO_Read(0,&port0);
        door_if.DIO_Read(1,&port1);

    }else if (!door_real.quit_hardware_flag){
        door_real.DIO_Read(0,&port0);
        door_real.DIO_Read(1,&port1);
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


    if(!door_if.quit_simulator_flag) {// bedingung für Simulator

        door_if.DIO_Write(2,port2);

    }else if (!door_real.quit_hardware_flag){
        door_real.DIO_Write(2,port2);
    }


}


void DoorControl::iniAutomatik() {

    std::map<std::string, State*> states;

    states["Init"]   = new State("Init",a_enterInit,MotorOf,a_exit);
    states["Zu"] = new State("Zu",MotorOf,MotorOf,defaultFunc);
    states["Auf"] = new State("Auf",MotorOf,MotorOf,defaultFunc);
    states["Oeffnen"] = new State("Oeffnen",doorOpen,doorOpen,defaultFunc);
    states["Schliessen"] = new State("Schliessen",doorClose,doorClose,defaultFunc);

    std::list<Transition*> transitions;

    trlist_automatik.push_back(new Transition (*states["Init"],*states["Zu"],d_ELG));
    trlist_automatik.push_back(new Transition (*states["Init"],*states["Oeffnen"],d_notEloElg));
    trlist_automatik.push_back(new Transition (*states["Init"],*states["Auf"],d_ELO));
    trlist_automatik.push_back(new Transition (*states["Auf"],*states["Auf"],a_NtaLasLsvBm));
    trlist_automatik.push_back(new Transition (*states["Auf"],*states["Schliessen"],a_Auf_schliessen));
    trlist_automatik.push_back(new Transition (*states["Oeffnen"],*states["Auf"],d_ELO));
    trlist_automatik.push_back(new Transition (*states["Oeffnen"],*states["Schliessen"],d_NTZ));
    trlist_automatik.push_back(new Transition (*states["Schliessen"],*states["Zu"],d_ELG));
    trlist_automatik.push_back(new Transition (*states["Schliessen"],*states["Oeffnen"],a_NtaLasLsvBm));
    trlist_automatik.push_back(new Transition (*states["Zu"],*states["Oeffnen"],a_NtaLasLsvBm));

    automatik = new Automat(trlist_automatik,*states["Init"]);

}

void DoorControl::iniHandbetrieb() {

    std::map<std::string, State*> states;

    states["Init"] = new State ("Init",d_AktorenOf,d_AktorenOf,defaultFunc);
    states["Zu"] = new State ("Zu",MotorOf,MotorOf,defaultFunc);
    states["Auf"] = new State ("Auf",MotorOf,MotorOf,defaultFunc);
    states["Oeffnen"] = new State ("Oeffnen",doorOpen,doorOpen,defaultFunc);
    states["Schliessen"] = new State ("Schliessen",doorClose,doorClose,defaultFunc);
    states["Stop"] = new State ("Stop",MotorOf,MotorOf,defaultFunc);

    std::list<Transition*> transitions;

    trlist_handbetrieb.push_back(new Transition (*states["Init"],*states["Zu"],d_ELG));
    trlist_handbetrieb.push_back(new Transition (*states["Init"],*states["Auf"],d_ELO));
    trlist_handbetrieb.push_back(new Transition (*states["Init"],*states["Stop"],d_notEloElg));
    trlist_handbetrieb.push_back(new Transition (*states["Zu"],*states["Oeffnen"],d_NTA));
    trlist_handbetrieb.push_back(new Transition (*states["Oeffnen"],*states["Auf"],d_ELO));
    trlist_handbetrieb.push_back(new Transition (*states["Oeffnen"],*states["Stop"],d_notNtaNtz));
    trlist_handbetrieb.push_back(new Transition (*states["Oeffnen"],*states["Oeffnen"],d_NTA));
    trlist_handbetrieb.push_back(new Transition (*states["Oeffnen"],*states["Schliessen"],d_NTZ));
    trlist_handbetrieb.push_back(new Transition (*states["Schliessen"],*states["Oeffnen"],d_NTA));
    trlist_handbetrieb.push_back(new Transition (*states["Schliessen"],*states["Schliessen"],d_NTZ));
    trlist_handbetrieb.push_back(new Transition (*states["Schliessen"],*states["Zu"],d_ELG));
    trlist_handbetrieb.push_back(new Transition (*states["Schliessen"],*states["Stop"],d_notNtaNtz));
    trlist_handbetrieb.push_back(new Transition (*states["Auf"],*states["Schliessen"],d_NTZ));
    trlist_handbetrieb.push_back(new Transition (*states["Stop"],*states["Schliessen"],d_NTZ));
    trlist_handbetrieb.push_back(new Transition (*states["Stop"],*states["Oeffnen"],d_NTA));
    trlist_handbetrieb.push_back(new Transition (*states["Stop"],*states["Stop"],h_Stop_Stop));

    handbetrieb = new Automat(transitions,*states["Init"]);

}
void DoorControl::iniReparaturmodus() {

    std::map<std::string, State*> states;

    states["Init"] = new State ("Init",d_AktorenOf,d_AktorenOf,defaultFunc);
    states["Zu"] = new State ("Zu",d_AktorenOf,d_AktorenOf,defaultFunc);
    states["Auf"] = new State ("Auf",d_AktorenOf,d_AktorenOf,defaultFunc);
    states["Oeffnen"] = new State ("Oeffnen",r_oeffnen,r_oeffnen,defaultFunc);
    states["Schliessen"] = new State ("Schliessen",r_schliessen,r_schliessen,defaultFunc);
    states["Stop"] = new State ("Stop",d_AktorenOf,d_AktorenOf,defaultFunc);

    std::list<Transition*> transitions;

    trlist_reparatur.push_back(new Transition (*states["Init"],*states["Stop"],d_notEloElg));
    trlist_reparatur.push_back(new Transition (*states["Init"],*states["Auf"],d_ELO));
    trlist_reparatur.push_back(new Transition (*states["Init"],*states["Zu"],d_ELG));
    trlist_reparatur.push_back(new Transition (*states["Stop"],*states["Schliessen"],r_NTZ_notAll));
    trlist_reparatur.push_back(new Transition (*states["Stop"],*states["Stop"],r_Stop_Stop));
    trlist_reparatur.push_back(new Transition (*states["Oeffnen"],*states["Stop"],r_oeffnen_Stop));
    trlist_reparatur.push_back(new Transition (*states["Oeffnen"],*states["Schliessen"],r_NTZ_notAll));
    trlist_reparatur.push_back(new Transition (*states["Oeffnen"],*states["Auf"],d_ELO));
    trlist_reparatur.push_back(new Transition (*states["Auf"],*states["Schliessen"],r_NTZ_notAll));
    trlist_reparatur.push_back(new Transition (*states["Schliessen"],*states["Zu"],d_ELG));
    trlist_reparatur.push_back(new Transition (*states["Schliessen"],*states["Oeffnen"],r_allNotNTZ));
    trlist_reparatur.push_back(new Transition (*states["Schliessen"],*states["Stop"],r_notNTZ));
    trlist_reparatur.push_back(new Transition (*states["Stop"],*states["Stop"],r_Stop_Stop));

    reparatur = new Automat(transitions,*states["Init"]);

}
