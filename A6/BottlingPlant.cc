#include <algorithm>
#include "rng.h"
#include "BottlingPlant.h"
#include "Truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments)

 {
 	// create production array
 	isShutDown = false;
 }

 void BottlingPlant::main(){
 	prt.print(Printer::Kind::BottlingPlant, 'S');
 	// start by creating a new truck
 	Truck tr(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
 	for (;;){
		_Accept(~BottlingPlant){
			isShutDown = true;
			try {
				_Accept(getShipment);
			} catch (uMutexFailure::RendezvousFailure) {
				break;
			}
		} _Else {
		 	// Produce soda!
			unsigned int sum = 0;// sum of the soda being generated
			for (unsigned int i = 0; i < NUM_FLAVORS; i++){
				unsigned int newSoda = (rng() % maxShippedPerFlavour) + 1;
				produced[i] = newSoda;
				sum += newSoda;
			}
			prt.print(Printer::Kind::BottlingPlant, 'G', sum);
			yield(timeBetweenShipments);
			_Accept(getShipment);
		}

 	}
 	prt.print(Printer::Kind::BottlingPlant, 'F');
 }

void BottlingPlant::getShipment( unsigned int cargo[] ){
 	if (isShutDown){
 		throw Shutdown();
 	}
 	prt.print(Printer::Kind::BottlingPlant, 'P');
 	for (int i = 0; i < NUM_FLAVORS; i++){
 		cargo[i] = produced[i];
 		produced[i] = 0;
 	}
 }


 BottlingPlant::~BottlingPlant(){}