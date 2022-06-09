//
// Created by dustin on 6/8/22.
//

#ifndef ART_TEST_HARDWAREINTERFACE_H
#define ART_TEST_HARDWAREINTERFACE_H

#include <string>
#include <usb.h>
#include <atomic>


class HardwareInterface {
    public:
    // quit flag
    static std::atomic<bool> quit_hardware_flag;
    HardwareInterface();
    ~HardwareInterface(void);
    void DIO_Read(const unsigned port, unsigned char *pins);
    void DIO_Write(const unsigned port, const unsigned char pins);

private:
    struct usb_device *dev;
    struct usb_dev_handle *handle;

};


#endif //ART_TEST_HARDWAREINTERFACE_H
