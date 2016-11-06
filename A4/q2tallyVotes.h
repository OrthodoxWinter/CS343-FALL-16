#ifndef __TALLY_H__
#define __TALLY_H__

_Monitor Printer;

#include <uSemaphore.h>
#include <uBarrier.h>
#include <vector>

#if defined( IMPLTYPE_MC )            // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
	uCondLock entryQueue, voteQueue, bargeQueue;
	uOwnerLock lock;
	unsigned int count, voted, resultRead;
	bool noBarge;
	unsigned int pictureVotes, statueVotes;
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_SEM )         // semaphore solution
// includes for this kind of vote-tallier
class TallyVotes {
	uSemaphore entrySem, voteSem, lock;
	unsigned int voted;
	unsigned int pictureVotes, statueVotes;
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_BAR )         // barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
// private declarations for this kind of vote-tallier
	unsigned int count;
	std::vector<int> votes;
#else
	#error unsupported voter type
#endif
// common declarations
	const unsigned int groupSize;
	Printer &printer;
  public:                             // common interface
	TallyVotes( unsigned int group, Printer &printer );
	enum Tour { Picture, Statue };
	Tour vote( unsigned int id, Tour ballot );
};

#endif