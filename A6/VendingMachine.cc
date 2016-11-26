#include "VendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour): prt(prt),nameServer(nameServer),id(id),sodaCost(sodaCost),maxStockPerFlavour(maxStockPerFlavour){
	// initialize the inventory array
	inventory = new int[3];
	isRestocked  = false;
};


void VendingMachine:: buy( Flavours flavour, WATCard &card ){
	if (getBalance() < sodaCost){
			throw _Funds();
	}
	if (inventory[flavour] <= 0){
		throw _Stock();
	}
	card->withdraw(sodaCost);
};
void VendingMachine:: main(){
	nameServer->VMregister(*this);
	for (;;){
		_Accept(~VendingMachine){
			break;
		} or _Accept(restocked){

		} or _When(isRestocked) _Accept(buy);
	}
}

unsigned int VendingMachine:: *inventory(){
	return inventory;
}
void VendingMachine::restocked(){
	isRestocked = true;
}


VendingMachine:: ~VendingMachine(){
	delete[] inventory;
}

_Nomutex VendingMachine::unsigned int getId(){
	return id;
}

_Nomutex unsigned int cost(){
	return sodaCost;
}


