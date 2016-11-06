#ifndef __VOTER_H__
#define __VOTER_H__

#include "q2tallyVotes.h"

#if defined( IMPLTYPE_BAR )
_Cormonitor TallyVotes;
#else
class TallyVotes;
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