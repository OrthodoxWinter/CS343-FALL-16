#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>

TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : uBarrier(group), count(0), voteCount(0), groupSize(group), printer(printer) {}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	count++;															// new voter
	assert(count <= groupSize);
	if (ballot == Picture) {											// tally vote
		voteCount++;
	} else {
		voteCount--;
	}
	printer.print(id, Voter::States::Vote, ballot);	
	if (count < groupSize) {
		printer.print(id, Voter::States::Block, waiters() + 1);
		block();														// block and print message if not enough people to from group yet
		printer.print(id, Voter::States::Unblock, waiters());
	} else {
		pictureTour = voteCount > 0;									// group has been formed, get result and reset internal states
		printer.print(id, Voter::States::Complete);
		voteCount = 0;
		count = 0;
		block();
	}
	if (pictureTour) {
		return Picture;
	} else {
		return Statue;
	}
}