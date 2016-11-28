#include <algorithm>
#include "rng.h"
#include "BottlingPlant.h"
#include "Truck.h"
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxShippedPerFlavour), timeBetweenShipments(timeBetweenShipments)

 {
 	// create production array
 	produced = new unsigned int[3];
 	isShutDown = false;
 	finishPickUp = true;
 }

 void BottlingPlant::main(){
 	printer.print(Printer::Kind::BottlingPlant, 'S');
 	// start by creating a new truck
 	tr = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
 	for (;;){
 		 _Accept(~BottlingPlant){
 		 	isShutDown = true;
 		 	break;
 		 }
 		 if (finishPickUp){
 		 	 // Produce soda!
 		 	int sum = 0;// sum of the soda being generated

 		 	for (int i = 0; i < NUM_FLAVORS; i++){
 		 		int newSoda = rng(maxShippedPerFlavour);
 		 		produced[i] += newSoda;
 		 		sum += newSoda;
 		 	}
 		 	printer.print(Printer::Kind::BottlingPlant, 'G', sum);
 		 	yield(timeBetweenShipments);
 		 }

 	}
 	 printer.print(Printer::Kind::BottlingPlant, 'F');

 }

 void BottlingPlant::getShipment( unsigned int cargo[] ){
 	if (isShutDown){
 		_Throw Shutdown();
 	}
 	printer.print(Printer::Kind::BottlingPlant, 'P');
 	finishPickUp = false;
 	for (int i = 0; i < NUM_FLAVORS; i++){
 		cargo[i] = Min(maxShippedPerFlavour, produced[i]);
 		produced -= Min(maxShippedPerFlavour, produced[i]);
 	}
 	finishPickUp = true;
 };


 BottlingPlant::~BottlingPlant(){
 	delete tr;
 	delete[] produced;
 }