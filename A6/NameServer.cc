#include "NameServer.h"
#include "vendingMachine.h"
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): Printer(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new vendingMachine*[numVendingMachines];
		lastPos = 0;
	};

void VMregister(VendingMachine *vendingmachine){
	int id = vendingmachine.id;
	machineList[id] = vendingmachine;
}
VendingMachine * NameServer::getMachine(unsigned int id){
	int last = lastPos % numVendingMachines;
	lastPos += 1;
	return machineList[last];
} 
VendingMachine ** NameServer::getMachineList(){
	return machineList;
}

void NameServer::main(){
	for (;;;){
		_Accpept(~NameServer){
			break;
		} or _Accept(getMachineList, getMachine)
	}
}

NameServer::~NameServer(){
	delete machineList[];
}
