#include "Groupoff.h"

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay):prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay){};

void Groupoff::main(){
	for (;;){
		_Accept(~Groupoff) {
			break;
		} or _Accept(giftCard)
		_Else {
			yield(groupoffDelay);

		}
	}
}

WATCard::FWATCard Groupoff::giftCard(){
};