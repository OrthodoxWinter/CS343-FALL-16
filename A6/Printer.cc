#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers): numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers){
	unsigned int objectCount = 6 + numStudents + numVendingMachines + numCouriers; // The number of objects which need to be printed out;
	buffer = new State[objectCount];
	// Print all the objects;
	cout << "Parent\tGroupoff\tWATOFF\tNames\tTruck\tPlant\t";

	for (unsigned int i = 0; i < numStudents; i++){
		cout << "Stud" << i << "\t"; 
	}
	for (unsigned int i = 0; i < numVendingMachines; i++){
		cout << "Mach" << i << "\t";
	}

	for (unsigned int i = 0 ; i < numCouriers; i++){
		cout << "Cour" << i << "\t"
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++){
		cout << "*******\t";
	}
	cout << endl;

}


void Printer::print( Kind kind, char state ){
	buffer[kind].state = state;
	 
}


Printer::~Printer() {
	delete[] buffer;
}
