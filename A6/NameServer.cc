#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): prt(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
	// allocate the array
	machineList = new VendingMachine*[numVendingMachines];
	assignments = new int[numStudents];
	// Initial assignment of vending machine
	for (unsigned int i = 0; i < numStudents; i++){
		assignments[i] = i % numVendingMachines;
	}
	counter = 0;
};
/* Register the virtual machine */
void NameServer::VMregister(VendingMachine *vendingmachine){
	//add vm to list in chronological order
	prt.print(Printer::Kind::NameServer, 'R', vendingmachine->getId());
	machineList[counter] = vendingmachine;
	counter += 1;
}

VendingMachine* NameServer::getMachine(unsigned int id){
	//get machine to return
	VendingMachine* nextMachine = machineList[assignments[id]];
	prt.print(Printer::Kind::NameServer, 'N', id, assignments[id]);
	// Update the assignment to the next machine
	assignments[id] = (assignments[id] + 1) % numVendingMachines;
	return nextMachine;
}

VendingMachine ** NameServer::getMachineList(){
	return machineList;
}

void NameServer::main(){
	prt.print(Printer::Kind::NameServer, 'S');
	// first allow VM to register
	for (unsigned int i = 0; i < numVendingMachines; i++) {
		_Accept(VMregister);
	}
	for (;;){
		_Accept(~NameServer){
			break;
		} 
		or _Accept(getMachineList, getMachine); //getMachineList has higher priority to preventing starvation
	}
	prt.print(Printer::Kind::NameServer, 'F');

}

NameServer::~NameServer(){
	delete [] machineList;
	delete [] assignments;
}
