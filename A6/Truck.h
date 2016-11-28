#ifndef __TRUCK_H__
#define __TRUCK_H__
#include "printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
_Task BottlingPlant;
_Task Truck {
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int lastVendingMachine; // The last vending Machine restocked
    void main();
    int *cargo;// cargo to store soda
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};
#endif