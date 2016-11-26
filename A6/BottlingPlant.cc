#include "rng.h"
#include "BottlingPlant.h"
#include "Truck.h"
 BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxShippedPerFlavour), timeBetweenShipments(timeBetweenShipments)

 {
 	// create production array
 	production = new unsigned int[3];
 	isShutDown = false;
 	finishPickUp = true;
 }

 void BottlingPlant::main(){
 	// start by creating a new truck
 	tr = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
 	for (;;){
 		 _Accept(~BottlingPlant){
 		 	isShutDown = true;
 		 	break;
 		 }
 		 if (finishPickUp){
 		 	 // Produce soda!
 		 	for (int i = 0; i < 3; i++){
 		 		int randNum = rng(maxShippedPerFlavour);
 		 		production[i] += randNum;
 		 	}
 		 	 yield(timeBetweenShipments);
 		 }

 	}
 }

 void BottlingPlant::getShipment( unsigned int cargo[] ){
 	if (isShutDown){
 		_Throw Shutdown();
 	}
 	finishPickUp = false;
 	for (int i = 0; i < 3; i++){
 		if (production[i] > maxShippedPerFlavour){
 			cargo[i] = maxShippedPerFlavour;
 		} else {
 			cargo[i] = production[i];
 		}
 	}
 	finishPickUp = true;
 };


 BottlingPlant::~BottlingPlant(){
 	delete tr;
 	delete[] production;
 }