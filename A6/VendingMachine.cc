
#include "VendingMachine.h"
#include "NameServer.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour): prt(prt),nameServer(nameServer),id(id),sodaCost(sodaCost),maxStockPerFlavour(maxStockPerFlavour){
	// initialize the inventory array
	for (unsigned int i = 0; i < NUM_FLAVORS; i++) {
		ivty[i] = 0;
	}
	isRestocking  = false;
};


void VendingMachine::buy( Flavours flavour, WATCard &card ){
	if (card.getBalance() < sodaCost){
		_Throw Funds();
	}
	if (ivty[flavour] <= 0){
		_Throw Stock();
	}
	card.withdraw(sodaCost);
	ivty[flavour]--;
	prt.print(Printer::Kind::Vending, id, 'B', flavour, ivty[flavour]);
}

void VendingMachine::main(){
	prt.print(Printer::Kind::Vending, id, 'S', cost());
	nameServer.VMregister(this);
	for (;;){
		try {
			_Accept(~VendingMachine){
				break;
			} 
			or _When(isRestocking) _Accept(restocked);
			or _When(!isRestocking) _Accept(inventory, buy);
		} catch (uMutexFailure::RendezvousFailure) {
			
		}
	}
	prt.print(Printer::Kind::Vending, id, 'F', cost());

}

unsigned int* VendingMachine::inventory(){
	isRestocking = true;
	prt.print(Printer::Kind::Vending, id, 'r');
	return ivty;
}

void VendingMachine::restocked(){
	isRestocking = false;
	prt.print(Printer::Kind::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::getId(){
	return id;
}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}


