#ifndef __PARENT_H__
#define __PARENT_H__

#include "bank.h"
#include "printer.h"

_Task Parent {
	Printer &printer;
	Bank &bank; // bank to deposit money
	const unsigned int numStudents; // total number of student 
	const unsigned int parentalDelay;// delay for parent
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif