#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ): prt(prt), numVendingMachines(numVendingMachines),numStudents(numStudents){
		machineList = new VendingMachine*[numVendingMachines];
		lastPos = 0;
	};

void NameServer::VMregister(VendingMachine *vendingmachine){
	printer.print(Printer::kind:NameServer, 'R', vendingmachine->getId());
	machineList[counter] = vendingmachine;
	counter += 1;
}
VendingMachine * NameServer::getMachine(unsigned int id){
	int nextMachine = (id + 1) % numVendingMachines;
	return machineList[nextMachine];
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
	delete []machineList;
}
