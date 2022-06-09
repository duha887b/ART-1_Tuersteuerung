//
// Created by dustin on 6/9/22.
//

#ifndef ART_1_TUERSTEUERUNG_HARDWAREELEMENT_H
#define ART_1_TUERSTEUERUNG_HARDWAREELEMENT_H

#include <iostream>
class HardwareElement {
public:
    HardwareElement(unsigned int port, unsigned int pin, bool state);
    ~HardwareElement();
    virtual bool getState();
    void setState(bool pin);

protected:
    bool state;
    unsigned int pin;
    unsigned int port;

};


#endif //ART_1_TUERSTEUERUNG_HARDWAREELEMENT_H
