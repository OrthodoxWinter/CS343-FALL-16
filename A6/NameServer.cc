#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): prt(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new VendingMachine*[numVendingMachines];
		assignments = new int[numVendingMachines];
		// Initial assignment of vending machine
		for (unsigned int i = 0; i < numStudents; i++){
			assignments[i] = i % numVendingMachines;
		}
		counter = 0;
	};

void NameServer::VMregister(VendingMachine *vendingmachine){
	prt.print(Printer::Kind::NameServer, 'R', vendingmachine->getId());
	machineList[counter] = vendingmachine;
	counter += 1;
}
VendingMachine* NameServer::getMachine(unsigned int id){
	VendingMachine* nextMachine = machineList[assignments[id]];
	prt.print(Printer::Kind::NameServer, 'N', id, assignments[id]);
	// Update the assignment to the next Machine
	assignments[id] = (assignments[id] + 1) % numVendingMachines;
	return nextMachine;
} 
VendingMachine ** NameServer::getMachineList(){
	return machineList;
}

void NameServer::main(){
	prt.print(Printer::Kind::NameServer, 'S');
	for (;;){
		_Accept(~NameServer){
			break;
		} 
		or _When(counter < numVendingMachines) _Accept(VMregister);
		or _When(counter == numVendingMachines) _Accept(getMachineList, getMachine);
	}
	prt.print(Printer::Kind::NameServer, 'F');

}

NameServer::~NameServer(){
	delete [] machineList;
	delete [] assignments;
}
