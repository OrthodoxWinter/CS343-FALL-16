#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "printer.h"
#include "bank.h"
#include "WATcard.h"
#include "bank.h"

_Task WATCardOffice {
  private:
    struct Args {
        unsigned int sid;
        WATCard *card;
        unsigned int amount;
        Args(unsigned int sid, WATCard *card, unsigned int amount) : sid(sid), card(card), amount(amount) {}
    };

    struct Job {				// marshalled arguments and return future
        Args args;				// call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;			// return future
        Job(Args args) : args( args ) {}
    };

    _Task Courier {
      private:
        unsigned int id;
        WATCardOffice &office;
        Bank &bank;
        Printer &printer;
        void main();
      public:
        Courier(unsigned int id, WATCardOffice &office, Bank &bank, Printer &printer);
    };

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    Courier **couriers;
    Job *nextJob;
    bool terminate;
    void main();
  public:
    _Event Lost {};

    WATCardOffice(Printer &printer, Bank &bank, unsigned int numCouriers);
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
