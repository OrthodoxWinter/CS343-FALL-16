#ifndef __BOTTLINGPLANT_H
#define __BOTTLINGPLANT_H
#include "printer.h"
#include "Truck.h"
#include "NameServer.h"
_Task Truck;

_Task BottlingPlant {
	Printer &prt;
	NameServer &nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;
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