#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ); : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
	students = new State[numStudents];
	vendingMachines = new State[numVendingMachines];
	couriers new State[numCouriers];
	buffer = new State[voters];
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
	printLoop(6, "*******", false)
	printLoop(numStudents, "*******");
	printLoop(numVendingMachines, "*******");
	printLoop(numCouriers, "*******");
	cout << endl;
}

Printer::~Printer() {
	delete[] students;
	delete[] vendingMachines;
	delete[] couriers;
	cout << "***********************" << endl;
}

void Printer::printLoop(unsigned int times, string value, bool withIndex) {
	for (unsigned int i = 0; i < times; i++) {
		cout << value;
		if (withIndex) cout << i;
		cout << '\t';
	}
}