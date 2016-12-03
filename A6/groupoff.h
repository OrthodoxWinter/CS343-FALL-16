#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "WATcard.h"
#include "printer.h"

_Task Groupoff {
	Printer &printer;
	unsigned int numStudents;// total number of students
	unsigned int sodaCost; // soda costs
	unsigned int groupoffDelay; // groupoffDelay
	WATCard::FWATCard *futureCards;
	unsigned int nextFuture;
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
    ~Groupoff();
};

#endif