#include "DoorControl.h"
#include "config_handler.h"
#include "config_handler.h"
#include <fstream>
#include "iostream"

/* Das Programm in Eclipse mittels des Menüeintrags:
 * "Run -> External Tools" -> run in xterm"
 * starten!*/
int main (int argc, char *argv[])
{
    // ... maybe insert your class initialization here?
    // example:

    config_handler handler;
    handler.sensoren_get();

    /*
    DoorControl control;
    control.run();
    */

    return 0;
}
