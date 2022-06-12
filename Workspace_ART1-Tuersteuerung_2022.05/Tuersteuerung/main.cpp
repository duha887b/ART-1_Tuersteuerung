#include "DoorControl.h"
#include "config_handler.h"
#include "config_handler.h"
#include <fstream>
#include "iostream"

using namespace std;

/* Das Programm in Eclipse mittels des Menüeintrags:
 * "Run -> External Tools" -> run in xterm"
 * starten!*/
int main (int argc, char *argv[])
{
    // ... maybe insert your class initialization here?
    // example:

    config_handler handler;
    handler.run();
    //Sensor sens = handler.sens_list;
    //Aktor akt = handler.akt_list;

    for (int i=0;i<16;i++) {
        cout << "Sensor" << i << ": " << handler.sens_list[i]->getPin() << " / " << handler.sens_list[i]->getPort() << endl;
    }

    cout << "Aktor0: " << handler.akt_list[0]->getPin() << " / " << handler.akt_list[0]->getPort() << endl;

    /*
    DoorControl control;
    control.run();
    */

    return 0;
}
