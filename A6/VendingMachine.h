#ifndef __VENDINGMACHINE_H
#define __VENDINGMACHINE_H

#include "NameServer.h"
#include "printer.h"
#include "WATcard.h"

#define NUM_FLAVORS 4

_Task NameServer;
_Task VendingMachine {
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    bool isRestocking;
    unsigned int ivty[NUM_FLAVORS];
    void main();
  public:
    enum Flavours { GRAPE = 0, APPLE = 1, ORANGE = 2,PINEAPPPLE = 3};                    // flavours of soda (YOU DEFINE)
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif