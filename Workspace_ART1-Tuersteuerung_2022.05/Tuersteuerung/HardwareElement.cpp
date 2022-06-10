//
// Created by dustin on 6/9/22.
//

#include "HardwareElement.h"
#include <iostream>

HardwareElement::HardwareElement(unsigned int port, unsigned int pin, bool state) : port(port),
                                                                                    pin(pin),
                                                                                    state(state)
{

}

HardwareElement::~HardwareElement(){

}

bool HardwareElement::getState(){
    //std::cout << "nicht überladen" << std::endl;

    return state;
}

void HardwareElement::setState(bool pin) {
    state = pin;

}

unsigned int HardwareElement::getPort(){
    return port;

}
unsigned int HardwareElement::getPin(){
    return pin;
}