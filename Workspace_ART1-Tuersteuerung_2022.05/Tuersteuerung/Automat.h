/*
 * Automat.h
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */

#ifndef AUTOMAT_H_
#define AUTOMAT_H_
#include <list>
#include <iostream>
#include "State.h"
#include "Transition.h"

class Automat{

private:
	const std::list<Transition*>tr;
	const State* currentState;
	bool first;

public:

    Automat(const std::list<Transition*> tr, State& fs);
    Automat();
	void step();
    void restartAutomat();
    string getState();


};



#endif /* AUTOMAT_H_ */
