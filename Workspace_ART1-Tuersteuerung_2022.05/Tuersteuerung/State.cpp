/*
 * State.cpp
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */
#include "State.h"

State::State(const string id,Action enterFunc, Action stayFunc, Action exitFunc): name(id),enterFunc(enterFunc), stayFunc(stayFunc), exitFunc(exitFunc){

}


const string State::getName() {
    return name;
}
