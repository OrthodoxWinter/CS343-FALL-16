#ifndef __TRUCK_H__
#define __TRUCK_H__
#include "printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"

_Task BottlingPlant;
_Task Truck {
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int lastVendingMachine; // The last vending Machine restocked
    unsigned int cargo[NUM_FLAVORS];// cargo to store soda
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
#endif