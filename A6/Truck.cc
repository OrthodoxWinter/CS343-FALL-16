#include <algorithm>
#include "Truck.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"
#include "rng.h"
using namespace std;

 Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour){
 	lastVendingMachine = 0;
 }

void Truck::main(){
	prt.print(Printer::Kind::Truck, 'S');
	VendingMachine** vmList = nameServer.getMachineList();
	try {
		for (;;){
			yield(rng(9) + 1);
			plant.getShipment(cargo);
			unsigned int sum = 0;
			for (unsigned int i = 0; i < NUM_FLAVORS; i++){
				sum += cargo[i];
			}
			prt.print(Printer::Kind::Truck, 'P', sum);
			unsigned int counter = 0; // Counter for the number of VendingMachine it has vistied

			//Deliver to each vending machine
			while (true){
				VendingMachine* vm = vmList[lastVendingMachine];
				
				unsigned int machineId = vm->getId();
				prt.print(Printer::Kind::Truck, 'd', machineId, sum);
				
				unsigned int unfilled = 0;
				unsigned int* invent = vm->inventory();

				//restock each flavor
				for (int i = 0; i < NUM_FLAVORS; i++){
					if (invent[i] < maxStockPerFlavour && cargo[i] > 0){
						int toAdd = min(maxStockPerFlavour - invent[i], cargo[i]);
						cargo[i] -= toAdd;
						invent[i] += toAdd;
						sum -= toAdd;
					}
					//Unfill should be the cargo - toAdd
					unfilled += max((int) (cargo[i] - (maxStockPerFlavour - invent[i])) , 0);
				}

				//Call vending machine restock to notify it has been restocked
				vm->restocked();

				//not entirely sure about this unfilled thing. The description on the assignment is confusing
				if (unfilled > 0) {
					prt.print(Printer::Kind::Truck, 'U', machineId, unfilled);
				}

				prt.print(Printer::Kind::Truck, 'D', machineId, sum);
				lastVendingMachine = (lastVendingMachine + 1) % numVendingMachines;
				counter += 1;
				// check if the truck is empty (ie sum <= 0) or restocked all vending machines
				if (sum <= 0 || counter >= numVendingMachines) {
					break;
				}
			}
		}
	} catch(_Event BottlingPlant::Shutdown){

	}
}