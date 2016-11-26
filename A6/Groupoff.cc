#include "Groupoff.h"

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay):prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay){};

void Groupoff::main(){
	for (;;){
		_Accept(~Parent) {
			break;
		}
		_Else {
			yield(groupoffDelay);
			unsigned int amount = rng(2) + 1;
			unsigned int student = rng() % numStudents;
			bank.deposit(student, amount);
		}
	}
}