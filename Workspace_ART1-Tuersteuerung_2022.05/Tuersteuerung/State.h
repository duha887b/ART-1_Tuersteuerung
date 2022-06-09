/*
 * State.h
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */

#ifndef STATE_H_
#define STATE_H_

#include "Behaviour.h"

class State{
private:




public:
	Action enterFunc, stayFunc, exitFunc;

State(Action enterFunc, Action stayFunc, Action exitFunc);



};




#endif /* STATE_H_ */
