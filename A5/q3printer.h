#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "q3voter.h"
#include "q3tallyVotes.h"
#include <string>

struct State
{
	Voter::States state;
	TallyVotes::Tour vote;
	unsigned int numBlocked;
	unsigned int type;
};

_Monitor Printer {      // chose one of the two kinds of type constructor
	State* buffer;
	void flush();
	unsigned int voters;
	char toChar(TallyVotes::Tour tour);
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    ~Printer();
};

#endif