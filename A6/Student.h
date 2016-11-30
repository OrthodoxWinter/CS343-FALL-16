#ifndef __STUDENT_H__
#define __STUDENT_H__
#define INITIAL_AMOUNT 5
#include "NameServer.h"
#include "groupoff.h"
#include "WATcardoffice.h"
#include "WATcard.h"
_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
	unsigned int id;
	unsigned int maxPurchases;
	unsigned int numberToPurchase;
	VendingMachine::Flavours favouriteFlavour;
	WATCard::FWATCard card;/// watcard
	WATCard::FWATCard giftCard; // giftCard
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};

#endif