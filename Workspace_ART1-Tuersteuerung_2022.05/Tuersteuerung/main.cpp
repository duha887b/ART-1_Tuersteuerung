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
    Sensor* sens = handler.get_sens_list();
    Aktor* akt = handler.get_akt_list();

    for (int i=0;i<16;i++) {
        cout << "Sensor" << i << ": " << sens[i].getPin() << " / " << sens[i].getPort() << endl;
    }

    cout << "Aktor0: " << akt[0].getPin() << " / " << akt[0].getPort() << endl;

    /*
    DoorControl control;
    control.run();
    */

    return 0;
}
