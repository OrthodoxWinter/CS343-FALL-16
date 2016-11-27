#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )	 : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
	total = 6 + numStudents + numVendingMachines + numCouriers;
	states = new State[total];
	cout << "Parent" << '\t';
	cout << "Gropoff" << '\t';
	cout << "WATOff" << '\t';
	cout << "Names" << '\t';
	cout << "Truck" << '\t';
	cout << "Plant" << '\t';
	printLoop(numStudents, "Stud");
	printLoop(numVendingMachines, "Mach");
	printLoop(numCouriers, "Cour");
	cout << endl;
	printLoop(6, "*******", false);
	printLoop(numStudents, "*******", false);
	printLoop(numVendingMachines, "*******", false);
	printLoop(numCouriers, "*******", false);
	cout << endl;
}

Printer::~Printer() {
	delete[] states;
	cout << "***********************" << endl;
}

void Printer::printLoop(unsigned int times, string value, bool withIndex) {
	for (unsigned int i = 0; i < times; i++) {
		cout << value;
		if (withIndex) cout << i;
		cout << '\t';
	}
}

unsigned int Printer::getIndex(Kind kind, unsigned int id) {
	switch (kind) {
		case Student:
			return 6 + id;
		case Vending:
			return 6 + numStudents + id;
		case Courier:
			return 6 + numStudents + numVendingMachines + id;
		default:
			return (unsigned int) kind;
	}
}

void Printer::flush(string empty) {
	for (unsigned int i = 0; i < total; i++) {
		if (states[i].state == '\0') {
			cout << empty;
		} else {
			cout << states[i].state;
			if (states[i].value1 >= 0) {
				cout << states[i].value1;
				if (states[i].value2 >= 0) cout << ',' << states[i].value2;
			}
			states[i].state = '\0';
		}
		cout << '\t';
	}
	cout << endl;
}

void Printer::print(unsigned int index, State &newState) {
	if (newState.state == 'F') {
		for (unsigned int i = 0; i < total; i++) {
			if (states[i].state != '\0') {
				flush();
				break;
			}
		}
		states[index] = newState;
		flush("...");
	} else {
		if (states[index].state != '\0') flush();
		states[index] = newState;
	}
}

void Printer::print(Kind kind, char state) {
	unsigned int index = getIndex(kind);
	State newState(state);
	print(index, newState);
}

void Printer::print(Kind kind, char state, int value1) {
	unsigned int index = getIndex(kind);
	State newState(state, value1);
	print(index, newState);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	unsigned int index = getIndex(kind);
	State newState(state, value1, value2);
	print(index, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	unsigned int index = getIndex(kind, lid);
	State newState(state);
	print(index, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int index = getIndex(kind, lid);
	State newState(state, value1);
	print(index, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int index = getIndex(kind, lid);
	State newState(state, value1, value2);
	print(index, newState);
}