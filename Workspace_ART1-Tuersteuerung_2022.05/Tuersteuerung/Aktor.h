//
// Created by dustin on 6/10/22.
//

#ifndef ART_1_TUERSTEUERUNG_AKTOR_H
#define ART_1_TUERSTEUERUNG_AKTOR_H

#include "HardwareElement.h"

class Aktor : public HardwareElement{
public:
    explicit Aktor(unsigned int port, unsigned int pin, bool state);
    ~Aktor();

};


#endif //ART_1_TUERSTEUERUNG_AKTOR_H
