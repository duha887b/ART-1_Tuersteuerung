#include "DoorControl.h"
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

    //DoorControl control;
    //control.run();
    config_handler cfg_handler();
    cfg_handler.run();

    return 0;
}
