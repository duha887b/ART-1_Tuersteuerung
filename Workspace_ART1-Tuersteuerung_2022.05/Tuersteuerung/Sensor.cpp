//
// Created by dustin on 6/9/22.
//

#include "Sensor.h"


Sensor::Sensor(unsigned int port, unsigned int pin, bool state,bool opMode) : HardwareElement(port,pin,state), opMode(opMode)
{

}

Sensor::~Sensor() {
}

bool Sensor::getOpMode() {
    return opMode;


}
void Sensor::setOpMode(bool Mode) {
    opMode = Mode;
}

bool Sensor::getState() {
    if (!getOpMode()){
        state = !state;
    }
    return state;
}
