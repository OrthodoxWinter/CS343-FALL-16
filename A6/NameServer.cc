#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): prt(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new VendingMachine*[numVendingMachines];
		lastPos = 0;
	};

void NameServer::VMregister(VendingMachine *vendingmachine){
	int id = vendingmachine->getId();
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
	for (;;){
		_Accept(~NameServer){
			break;
		} or _Accept(getMachineList, getMachine)
	}
}

NameServer::~NameServer(){
	delete []machineList;
}
