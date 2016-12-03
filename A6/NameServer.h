#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__
#include "printer.h"
#include "VendingMachine.h"
_Task VendingMachine;
_Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;// total number of vending Machine
	unsigned int numStudents;// total number of students
	unsigned int counter; // Number of registered Machine
	VendingMachine ** machineList;// internal machine list
	int *assignments;// Array to store each student's machine
	void main();
	public:
		NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
		void VMregister( VendingMachine *vendingmachine );
		VendingMachine * getMachine( unsigned int id );
		VendingMachine **	getMachineList();
		~NameServer();
};
#endif