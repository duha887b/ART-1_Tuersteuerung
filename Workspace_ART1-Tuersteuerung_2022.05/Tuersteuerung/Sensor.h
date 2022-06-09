//
// Created by dustin on 6/9/22.
//

#ifndef ART_1_TUERSTEUERUNG_SENSOR_H
#define ART_1_TUERSTEUERUNG_SENSOR_H

#include "HardwareElement.h"


class Sensor :  public HardwareElement{
public:

    explicit Sensor(unsigned int port, unsigned int pin, bool state,bool opMode);
    ~Sensor();
    bool getOpMode();
    void setOpMode(bool Mode);
    bool getState();

private:
    bool opMode;


};


#endif //ART_1_TUERSTEUERUNG_SENSOR_H
