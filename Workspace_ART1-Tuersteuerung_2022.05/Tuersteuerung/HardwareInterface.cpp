//
// Created by dustin on 6/8/22.
//

#include "HardwareInterface.h"
#include "Library/niusb6501.h"
#include <iostream>
#include <string.h>



//static member for exit requests
std::atomic<bool> HardwareInterface::quit_hardware_flag(false);

HardwareInterface::HardwareInterface()
{

    if( niusb6501_list_devices(&dev, 1) != 1) {
        throw std::runtime_error("Device not found");
    }
    handle = niusb6501_open_device(dev);
    if (handle == NULL){
        throw std::runtime_error("Unable to open the USB device");
    }
    niusb6501_set_io_mode(handle, 0x03, 0x00, 0xFF);
}

HardwareInterface::~HardwareInterface(void)
{

}

void HardwareInterface::DIO_Read(const unsigned port, unsigned char *pins)
{

    int status;

    status = niusb6501_read_port(handle, port, pins);
    if(status) {
        std::cerr << "error read port " << port << ": " << strerror(-status) << std::endl;
    }

}

void HardwareInterface::DIO_Write(const unsigned port, const unsigned char pins)
{
    if(port != 2){
        std::cerr << "error write to port " << port << std::endl;
        return;
    }

    unsigned char p;
    int status;

    p = pins ^ 0xFF;
    status = niusb6501_write_port(handle, 2, p);
    if(status) {
        std::cerr << "error write port 2: " << strerror(-status) <<std::endl;
    }
}