#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "q2voter.h"
#include "q2tallyVotes.h"
#include <string>
#include <vector>

_Monitor Printer {      // chose one of the two kinds of type constructor
	std::vector<std::string> buffer;
	void print( unsigned int id, std::string state);
	void flush( std::string value = "" );
	unsigned int voters;
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif