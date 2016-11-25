#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <queue>
#include "WATcard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice {
    struct Args {
        unsigned int id;
        unsigned int amount;
        WATCard *card;
        Args( unsigned int id, unsigned int amount, WATCard *card ) : id(id), amount(amount), card(card) {}
    }

    struct Job {                              // marshalled arguments and return future
        Args args;                            // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;             // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
        Bank &bank;
        WATCardOffice &office;
      public:
        main();
        Courier(Bank &bank, WATCardOffice &office);
    };                    // communicates with bank

    queue<Job*> jobs;
    Courier** couriers;
    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    bool terminate;
    void main();
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
    ~WATCardOffice();
};

#endif