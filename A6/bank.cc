#include "bank.h"

Bank::Bank(unsigned int numStudents) {
	amount = new unsigned int[numStudents];
	toWithdraw = new unsigned int[numStudents];
	bench = new uCondition[numStudents];
	for (int i = 0; i < numStudents; i++) {
		amount[i] = 0;
		toWithdraw[i] = 0;
	}
}

void Bank::deposit(unsigned int id, unsigned int amount) {
	amount[id] += amount;
	if (amount[id] >= toWithdraw[id]) {
		toWithdraw[id] = 0;
		bench[id].signal();
	}
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	if (amount[id] <= amount) {
		toWithdraw[id] = amount;
		bench[id].wait();
	}
	amount[id] -= amount;
}

Bank::~Bank() {
	delete[] amount;
	delete[] bench;
	delete[] toWithdraw;
}