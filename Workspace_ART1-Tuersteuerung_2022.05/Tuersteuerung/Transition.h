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
	const State& startState;
	const State& endState;
	Condition bedingung;
	Transition (const State& start, const State& end, Condition bed);


};



#endif /* TRANSITION_H_ */
