#include "DoorControl.h"
#include <fstream>
#include "test.h"
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

    Zustand st1(1);
    Zustand st2(15);
    st1.print();
    st2.print();

	return 0;
}
