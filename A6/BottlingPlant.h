#ifndef __BOTTLINGPLANT_H
#define __BOTTLINGPLANT_H
#include "printer.h"
#include "Truck.h"
#include "NameServer.h"
_Task Truck;

_Task BottlingPlant {
	Printer &prt;
	NameServer &nameServer; // an administrator task used to manage the vending machine 
	unsigned int numVendingMachines; // The total number of Vending machine
	unsigned int maxShippedPerFlavour;// Max amount of soda per shipping 
	unsigned int maxStockPerFlavour;// Maximum stock of each flavor
	unsigned int timeBetweenShipments; // Time between each shipments
	unsigned int produced[NUM_FLAVORS]; // production
	bool isShutDown;// flag to know if it is shut down
    void main();
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};
#endif