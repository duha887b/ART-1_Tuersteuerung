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





DoorControl::DoorControl() : door_if( true) ,
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

void DoorControl::turnOff(){

}

void DoorControl::iniHandbetrieb(){

}
void DoorControl::iniReperatur(){

}

void DoorControl::iniAutomatik(){

}

void DoorControl::switchStepAutomat(){

}

void DoorControl::stepHandbetrieb(){

}

void DoorControl::stepReperatur(){

}

void DoorControl::stepAutomatik(){

}