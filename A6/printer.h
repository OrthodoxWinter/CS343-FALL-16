#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>

struct State
{
	unsigned int lid;
	bool hasId;
	char state;		// state == '' indicates empty state
	int value1;
	int value2;

};

_Monitor Printer {
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	State parent;
	State groupoff;
	State wATCardOffice;
	State nameServer;
	State truck;
	State bottlingPlant;
	State *students;
	State *vendingMachines;
	State *Courier;
	State getState(Kind kind);
	void flush();
	void printLoop( unsigned int times, string value, bool withIndex = true );
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};
#endif