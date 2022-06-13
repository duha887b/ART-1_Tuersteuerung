/*
 * Automat.cpp
 *
 *  Created on: 08.06.2022
 *      Author: mrt
 */

#include<iostream>
using namespace std;
#include "Automat.h"

Automat::Automat() {

}

Automat::Automat(std::list<Transition*> tr, State& fs): tr(tr),currentState(&fs),first(true){

}


void Automat::restartAutomat() {
    first = true;
}

string Automat::getState() {
    return currentState->name;
}

void Automat::step(){


	if (first){
		currentState->enterFunc();
		first=false;
	}


	for (std::list<Transition *>::const_iterator i = tr.begin(); i != tr.end();i++){

		Transition *t = *(i);
		if(&t->startState == currentState){

			if(t->bedingung()){
				currentState->exitFunc();
				currentState = &t->endState;
				currentState->enterFunc();
				return;
			}

		}


	}
	currentState->stayFunc();

}
