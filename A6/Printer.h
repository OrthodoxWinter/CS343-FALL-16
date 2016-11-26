#ifndef __PRINTER_H__
#define __PRINTER_H__

struct State
{
	Kind kind;
	int type;
	char state;
	int value1;
	int value2;
	unsigned int lid;

};


_Monitor Printer {
	State* buffer;
	void flush();

	unsigned int numStudents, unsigned int numVendingMachines. unsigned int numCouriers;
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
    void printHelper(Kind kind, int count);
    ~Printer();
};