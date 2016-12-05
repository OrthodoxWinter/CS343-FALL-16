#include "parent.h"
#include "rng.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
	printer.print(Printer::Kind::Parent, 'S');
	for (;;) {
		//Accept destructor
		_Accept(~Parent) {
			break;
		}
		_Else {
			yield(parentalDelay);
			//Give random amount of money
			unsigned int amount = rng(2) + 1;
			unsigned int student = rng() % numStudents;
			// deposit that number of amount
			bank.deposit(student, amount);
		}
	}
	printer.print(Printer::Kind::Parent, 'F');
}