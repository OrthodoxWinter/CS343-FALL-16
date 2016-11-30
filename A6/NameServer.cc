#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): prt(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new VendingMachine*[numVendingMachines];
		// Initial assignment of vending machine
		for (unsigned int i = 0; i < numStudents; i++){
			assignments[i] = i % numVendingMachines;
		}
	};

void NameServer::VMregister(VendingMachine *vendingmachine){
	printer.print(Printer::Kind:NameServer, 'R', vendingmachine->getId());
	machineList[counter] = vendingmachine;
	counter += 1;
}
VendingMachine * NameServer::getMachine(unsigned int id){
	VendingMachine* nextMachine = machinelist[assignments[id]];
	int nextMachine = (id + 1) % numVendingMachines;
	printer.print(Printer::Kind::NameServer, 'N', id, nextMachine);
	assignments[id] = (assignments[id] + 1) % numVendingMachines;
	return nextMachine;
} 
VendingMachine ** NameServer::getMachineList(){
	return machineList;
}

void NameServer::main(){
	printer.print(Printer::Kind::NameServer, 'S');
	for (;;){
		_Accept(~NameServer){
			break;
		} or _Accept(getMachineList, getMachine)
	}
	printer.print(Printer::Kind::NameServer, 'F');

}

NameServer::~NameServer(){
	delete [] machineList;
	delete [] assignments;
}
