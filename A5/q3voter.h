#ifndef __VOTER_H__
#define __VOTER_H__

#include "q3tallyVotes.h"

#if defined( IMPLTYPE_TASK )
_Task TallyVotes;
#else
_Monitor TallyVotes;
#endif  

_Task Voter {
	const unsigned int id;
	TallyVotes &voteTallier;
	Printer &printer;
	void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                  Complete = 'C', Finished = 'F' };
    Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer);
};

#endif