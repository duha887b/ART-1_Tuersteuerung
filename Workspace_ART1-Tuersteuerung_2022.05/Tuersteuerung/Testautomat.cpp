/*
 * Testautomat.cpp
 *
 *  Created on: 09.06.2022
 *      Author: mrt
 */
#include <list>
#include <iostream>

#include "Automat.h"
#include "State.h"
#include "Transition.h"
using namespace std;

void tempFunc(){

	std::cout<<("Dies geht über einen Funktionszeiger")<<endl;
}

void tempFuncTwo(){

	std::cout<<("Ebenfalls über Zeiger")<<endl;
}

void defaultFunc(){

	std::cout<<("Nix")<<endl;

}

bool guardFunc(){
	return true;
}

void doNothingFunc(){


}

void Test ()
{

	//kleiner Testautomat mit zwei Zuständen, welcher zwischen diesen pendelt.
	//war meine main-Funktion zum testen


	State firstState (&tempFunc, &defaultFunc, &doNothingFunc);
	State secondState (&tempFuncTwo, &defaultFunc, &doNothingFunc);


	Transition tr(&firstState, &secondState, &guardFunc);
	Transition tr2(&secondState, &firstState, &guardFunc);

	std::list<Transition*>trlist;
	trlist.push_back(&tr);
	trlist.push_back(&tr2);

	Automat tempAutomat(trlist,&firstState);

	tempAutomat.step();
	tempAutomat.step();
	tempAutomat.step();

}



