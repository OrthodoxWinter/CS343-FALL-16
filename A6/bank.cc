#include "bank.h"

Bank::Bank(unsigned int numStudents) {
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
		bench[id].signal();
	}
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	if (bankAmount[id] < amount) {
		toWithdraw[id] = amount;
		bench[id].wait();
	}
	bankAmount[id] -= amount;
}

Bank::~Bank() {
	delete[] bankAmount;
	delete[] bench;
	delete[] toWithdraw;
}