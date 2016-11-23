#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;														// increment count
	printer.print(id, Voter::States::Vote, ballot);
	if (ballot == Picture) {										// cast vote
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count < groupSize) {										// if not enough members to form a group, then accept a new voter
		printer.print(id, Voter::States::Block, count);
		_Accept(vote);
		count--;													// decrement count after wake up. Conceptually count is the number of voters waiting to go on tour
		printer.print(id, Voter::States::Unblock, count);
	} else {
		result = pictureTour > 0 ? Picture : Statue;				// compute the result of the vote
		count--;													// decrement count
		pictureTour = 0;											// reset vote for next round
		printer.print(id, Voter::States::Complete);
	}
	return result;
}