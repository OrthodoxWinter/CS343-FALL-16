#include "NameServer.h"
#include "vendingMachine.h"
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): Printer(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new vendingMachine*[numVendingMachines];
	};

void VMregister(VendingMachine *vendingmachine){
	int id = vendingmachine.id;
	machineList[id] = vendingmachine;
}
VendingMachine * NameServer::getMachine(unsigned int id){
	
} 
VendingMachine ** NameServer::getMachineList(){
	return machineList;
}

