#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )	 : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
	total = 6 + numStudents + numVendingMachines + numCouriers;
	states = new State[total];
	cout << "Parent" << '\t';
	cout << "Groupoff" << '\t';
	cout << "WATOff" << '\t';
	cout << "Names" << '\t';
	cout << "Truck" << '\t';
	cout << "Plant" << '\t';
	printLoop(numStudents, "Stud");
	printLoop(numVendingMachines, "Mach");
	printLoop(numCouriers, "Cour");
	cout << endl;
	printLoop(6, "*******", false);
	printLoop(numStudents, "*******");
	printLoop(numVendingMachines, "*******");
	printLoop(numCouriers, "*******");
	cout << endl;
	for (int i = 0; i < total; i++) {
		states[i].state = '';
	}
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

void State& Printer::getState(Kind kind, unsigned int id) {
	switch (kind) {
		case Student:
			return states[6 + id];
		case Vending:
			return states[6 + numStudents + id];
		case Courier:
			return states[6 + numStudents + numVendingMachines + id];
		default:
			return states[kind];
	}
}

void flush(string empty) {
	for (unsigned int i = 0; i < total; i++) {
		State &state = states[i];
		if (state.state == '') {
			cout << empty;
		} else {
			cout << state.state;
			if (state.value1 >= 0) {
				cout << state.value1;
				if (state.value2 >= 0) cout << ',' << value2;
			}
		}
		state.state = '';
		cout << '\t';
	}
	cout << endl;
}

void Printer::print(State &state, State &newState) {
	if (newState.state == 'F') {
		flush();
		state = newState;
		flush("...");
	} else {
		if (state.state != '') flush();
		state = newState;
	}
}

void Printer::print(Kind kind, char state) {
	State &state = getState(kind);
	State newState(state);
	print(state, newState);
}

void Printer::print(Kind kind, char state, int value1) {
	State &state = getState(kind);
	State newState(state, value1);
	print(state, newState);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	State &state = getState(kind);
	State newState(state, value1, value2);
	print(state, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	State &state = getState(kind, lid);
	State newState(state);
	print(state, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	State &state = getState(kind, lid);
	State newState(state, value1);
	print(state, newState);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	State &state = getState(kind, lid);
	State newState(state, value1, value2);
	print(state, newState);
}