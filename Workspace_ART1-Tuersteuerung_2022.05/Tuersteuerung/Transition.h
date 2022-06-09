/*
 * Transition.h
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_
#include "Behaviour.h"
#include "State.h"

class Transition{
private:


public:
	State* startState;
	State* endState;
	Condition bedingung;
	Transition (State* start, State* end, Condition bed);


};



#endif /* TRANSITION_H_ */
