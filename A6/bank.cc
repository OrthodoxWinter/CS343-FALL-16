#include "bank.h"

Bank::Bank(unsigned int numStudents) {
	//Initialize bankAmount, toWithdraw array and the bench
	bankAmount = new unsigned int[numStudents];
	toWithdraw = new unsigned int[numStudents];
	bench = new uCondition[numStudents];
	for (unsigned int i = 0; i < numStudents; i++) {
		bankAmount[i] = 0;
		toWithdraw[i] = 0;
	}
}

void Bank::deposit(unsigned int id, unsigned int amount) {
	bankAmount[id] += amount;
	if (bankAmount[id] >= toWithdraw[id]) {
		toWithdraw[id] = 0;
		bench[id].signal();// notify the student siting in the bench that we have enough money right now
	}
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	if (bankAmount[id] < amount) {
		toWithdraw[id] = amount;
		bench[id].wait(); // sit on the bench wait for deposit
	}
	bankAmount[id] -= amount;
}

Bank::~Bank() {
	//Do clean up!
	delete[] bankAmount;
	delete[] bench;
	delete[] toWithdraw;
}