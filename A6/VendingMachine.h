#ifndef __VENDINGMACHINE_H
#define __VENDINGMACHINE_H
#include "NameServer.h"
#include "printer.h"
#include "WATcard.h"
_Task NameServer;
_Task VendingMachine {
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    bool isRestocked;
    int *ivty;
    void main();
  public:
    enum Flavours { GRAPE, APPLE, ORANGE };                    // flavours of soda (YOU DEFINE)
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
    ~VendingMachine();
};

#endif