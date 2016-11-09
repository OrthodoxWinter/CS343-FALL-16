#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>
#include <iostream>

using namespace std;

TallyVotes::TallyVotes(unsigned int group, Printer &printer) : groupSize(group), printer(printer) {
	count = 0;
	pictureVotes = 0;
	statueVotes = 0;
	noBarge = false;
	pictureTour = false;
}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	Tour result;
	lock.acquire();															// lock for mutex
	if (noBarge) {
		printer.print(id, Voter::States::Barging);							// if no barging, then block
		bargeQueue.wait(lock);
	}
	count++;																// increment count
	if (ballot == Picture) {												// cast vote
		pictureVotes++;
	} else {
		statueVotes++;
	}

	printer.print(id, Voter::States::Vote, ballot);

	if (count < groupSize) {												// not enough people to form a group
		if (!bargeQueue.empty()) {											// attempt to wake up someone from barge queue
			bargeQueue.signal();
			noBarge = true;
		} else {
			noBarge = false;												// nobody waiting, so reset barge flag
		}
		printer.print(id, Voter::States::Block, count);
		voteQueue.wait(lock);												// block until more voters arrive to form group
		count--;
		printer.print(id, Voter::States::Unblock, count);
	} else {
		printer.print(id, Voter::States::Complete);							// enough people voted to form a group
		pictureTour = pictureVotes > statueVotes;							// save result of election
		pictureVotes = 0;													// reset state
		statueVotes = 0;
		count--;
	}
	if (!voteQueue.empty()) {												// if more people waiting to read result, then wake one up
		voteQueue.signal();
		noBarge = true;
	} else if (!bargeQueue.empty()) {										// last person to read result, so try to let next group in
		bargeQueue.signal();												// wake one from barge
		noBarge = true;
	} else {
		noBarge = false;													// nobody waiting from barge queue, so reset noBarge
	}
	if (pictureTour) {														// return result
		result = Picture;
	} else {
		result = Statue;
	}
	lock.release();
	return result;
}