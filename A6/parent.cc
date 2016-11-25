#include "parent.h"
#include "rng.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
	for (;;) {
		_Accept(~Parent) {
			break;
		}
		_Else {
			yield(parentalDelay);
			unsigned int amount = rng(2) + 1;
			unsigned int student = rng() % numStudents;
			bank.deposit(student, amount);
		}
	}
}