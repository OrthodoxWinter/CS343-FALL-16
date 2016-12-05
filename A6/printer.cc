#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )	 : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
	total = 6 + numStudents + numVendingMachines + numCouriers;
	states = new State[total];
	//printer the header
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
	//printer the footer
	cout << "***********************" << endl;
}

//print the same string n times, separated by tabs. Optionally append index at the end of string
void Printer::printLoop(unsigned int times, string value, bool withIndex) {
	for (unsigned int i = 0; i < times; i++) {
		cout << value;
		if (withIndex) cout << i;
		cout << '\t';
	}
}

//get the corresponding index in the state array
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

//flushes all the states and set each to empty. Takes a parameter for what to print for empty states
void Printer::flush(string empty) {
	for (unsigned int i = 0; i < total; i++) {
		//'\0' represents empty state
		if (states[i].state == '\0') {
			cout << empty;
		} else {
			//print out the state
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

//attempt to set state at index to newState. If old state is non-empty, then flush
void Printer::print(unsigned int index, State &newState) {
	//new State is 'F', so need to flush
	if (newState.state == 'F') {
		for (unsigned int i = 0; i < total; i++) {
			//if all states are empty, then don't flush because otherwise there would be an extra empty line
			if (states[i].state != '\0') {
				flush();
				break;
			}
		}
		//print out the F state
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