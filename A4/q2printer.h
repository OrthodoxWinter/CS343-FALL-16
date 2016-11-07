#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "q2voter.h"
#include "q2tallyVotes.h"
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
	std::string toString( Voter::States state, TallyVotes::Tour vote );
	void flush();
	unsigned int voters;
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    ~Printer();
};

#endif