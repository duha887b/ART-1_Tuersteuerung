#include "DoorControl.h"
#include "config_handler.h"
#include <fstream>
#include "iostream"
#include <vector>
#include <usb.h>
using namespace std;

/* Das Programm in Eclipse mittels des Menüeintrags:
 * "Run -> External Tools" -> run in xterm"
 * starten!*/
int main (int argc, char *argv[])
{
    // ... maybe insert your class initialization here?
    // example:

    DoorControl control;
    control.run();
    

    return 0;
}
