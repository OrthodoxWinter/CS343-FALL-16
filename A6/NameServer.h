#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__
#include "VendingMachine.h"
_Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	unsigned int count;
	VendingMachine ** machineList;
	int assignments[numVendingMachines];
	void main();
	public:
	NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine *
	vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine **	getMachineList();
	~NameServer();
};
#endif