#include "Truck.h"
#include "VendingMachine.h"
#include "rng.h"


 Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour){
 	cargo = new int[3];
 	lastVendingMachine = 0;
 }

void Truck::main(){
	VendingMachine** vmList = nameServer->getMachineList();
	try {
		OutterLoop:
		for (;;;){
			_Accept(~Truck){
				break;
		}
		int randnum = rng(9) + 1;
		yield(randnum);
		plant->getShipment(cargo);
		int count = 0; // Counter for the number of VendingMachine it has vistied
		while (true){
			VendingMachine vm = vmList[lastVendingMachine];
			int* invent = vm->inventory();
			for (int i = 0; i < 3; i++){
				if (invent[i] < maxStockPerFlavour && cargo[i] >= 0){
					int needToAdd = maxStockPerFlavour - invent[i];
					if (cargo[i] <= needToAdd){
						invent[i] += cargo[i];
						cargo[i] = 0;
					} else {
						cargo[i] -= needToAdd;
						invent[i] = maxStockPerFlavour;
					}
				}
			}
			lastVendingMachine += 1;
			counter += 1;
			// check if the truck is empty < 0
			int sum = 0
			for (int i = 0; i < 3; i++){
				sum += cargo[i];
			}
			if (sum <= 0 || counter == numVendingMachines){
				break OutterLoop;
			}
		}
	}
	} catch(_Event Shutdown){

	}
}

Truck::~Truck(){
	delete cargo[];
}