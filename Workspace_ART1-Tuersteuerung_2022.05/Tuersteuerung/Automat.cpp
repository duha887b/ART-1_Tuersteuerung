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

Automat::Automat(std::list<Transition*> tr, State *fs):tr(tr){
	firstState=fs;
	first=true;
}


void Automat::restartAutomat() {
    first = true;
}


void Automat::step(){


	if (first){
		firstState->enterFunc();
		first=false;
	}


	for (std::list<Transition*>::const_iterator i = tr.begin(); i != tr.end();i++){

		Transition* t = *(i);
		if(t->startState == firstState){

			if(t->bedingung){
				firstState->exitFunc();
				firstState = t->endState;
				firstState->enterFunc();
				return;
			}

		}


	}
	firstState->stayFunc();

}
