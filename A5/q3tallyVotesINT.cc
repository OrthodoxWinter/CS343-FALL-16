#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;													// increment count. Conceptually count is the number of voters waiting to go on a tour
	printer.print(id, Voter::States::Vote, ballot);
	if (ballot == Picture) {									// cast vote
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count < groupSize) {									// if need more members, then wait on queue
		printer.print(id, Voter::States::Block, count);
		voteQueue.wait();
		count--;												// decrement count on wake up
		printer.print(id, Voter::States::Unblock, count);
	} else {													// group formed
		result = pictureTour > 0 ? Picture : Statue;			// compute result of vote
		count--;
		pictureTour = 0;										// reset vote variable for next round
		printer.print(id, Voter::States::Complete);
		while (!voteQueue.empty()) voteQueue.signal();			// wake up all voter that are blocked
	}
	return result;
}