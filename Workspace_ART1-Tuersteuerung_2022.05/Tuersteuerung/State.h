/*
 * State.h
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */

#ifndef STATE_H_
#define STATE_H_

#include "Behaviour.h"
#include <string>
using namespace std;

class State{
private:


public:
	Action enterFunc, stayFunc, exitFunc;
    const string name;
    State(const string id, Action enterFunc, Action stayFunc, Action exitFunc);

    const string getName();



};




#endif /* STATE_H_ */
