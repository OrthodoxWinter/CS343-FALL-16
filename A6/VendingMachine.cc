
#include "VendingMachine.h"
#include "nameServer.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour): prt(prt),nameServer(nameServer),id(id),sodaCost(sodaCost),maxStockPerFlavour(maxStockPerFlavour){
	// initialize the inventory array
	for (unsigned int i = 0; i < NUM_FLAVORS; i++) {
		ivty[i] = 0;
	}
	isRestocking  = false;
};


void VendingMachine:: buy( Flavours flavour, WATCard &card ){
	if (card.getBalance() < sodaCost){
		_Throw Funds();
	}
	if (ivty[flavour] <= 0){
		_Throw Stock();
	}
	card.withdraw(sodaCost);
	ivty[flavour]--;
	printer.print(Printer::Kind:VendingMachine, 'B', flavour, ivty[flavour]);
}

void VendingMachine:: main(){
	nameServer.VMregister(*this);
	printer.print(Printer::Kind:VendingMachine, 'S', vendingmachine->cost());
	for (;;){
		_Accept(~VendingMachine){
			break;
		} 
		or _When(isRestocking) _Accept(restocked);
		or _When(!isRestocking) _Accept(buy, inventory);
	}
	printer.print(Printer::Kind:VendingMachine, 'F', vendingmachine->cost());

}

unsigned int* VendingMachine:: inventory(){

	isRestocking = true;
	printer.print(Printer::Kind:VendingMachine, 'r');

	return ivty;
}

void VendingMachine::restocked(){
	isRestocking = false;
	printer.print(Printer::Kind:VendingMachine, 'R');

}


VendingMachine:: ~VendingMachine(){}

_Nomutex unsigned int VendingMachine:: getId(){
	return id;
}

_Nomutex unsigned int VendingMachine:: cost(){
	return sodaCost;
}


