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
	std::list<Transition*>tr;
	State* firstState;
	bool first;

public:

	Automat(std::list<Transition*> tr, State* fs);
	void step();


};



#endif /* AUTOMAT_H_ */
