#include "rng.h"

 BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments){

 }{
 	// create production array
 	production = new int[3];
 	isShutDown = false;
 	finishPickUp = true;
 }

 BottlingPlant::main(){
 	// start by creating a new truck
 	Truck *truck = new Truck(prt, plant, numVendingMachines, maxStockPerFlavour);
 	for (;;;){
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

 void getShipment( unsigned int cargo[] ){
 	if (isShutDown){
 		throw _ShutDown();
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
 	delete[] production;
 }