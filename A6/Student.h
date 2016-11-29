#ifndef __STUDENT_H__
#define __STUDENT_H__
#define INITIAL_AMOUNT 5
_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
	unsigned int id;
	unsigned int maxPurchases;
	unsigned int numberToPurchase;
	unsigned int favouriteFlavour;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif