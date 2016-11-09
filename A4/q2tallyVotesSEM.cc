#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	Tour result;
	entrySem.P();														// allow groupSize voters in at a time
	lock.P();															// acquire mutex lock for modifying state
	if (ballot == Picture) {											// cast vote
		pictureVotes++;
	} else {
		statueVotes++;
	}
	printer.print(id, Voter::States::Vote, ballot);
	voted++;
	assert(voted <= groupSize);
	if (voted == groupSize) {											// if enough people voted to form group, then waking up all those blocked
		assert(voteSem.counter() == (int) (-1 * (groupSize - 1)));
		printer.print(id, Voter::States::Complete);
		voteSem.V(groupSize - 1);
	} else {
		printer.print(id, Voter::States::Block, voted);					// if still need more people to form group, then wait
		voteSem.P(lock);
		lock.P();														// reacquire mutex lock on wake up
		printer.print(id, Voter::States::Unblock, voted - 1);
	}
	result = pictureVotes > statueVotes ? Picture : Statue;
	voted--;
	assert(voted >= 0);
	if (voted == 0) {													// reset variables when you're the last person from the group to read the vote
		pictureVotes = 0;
		statueVotes = 0;
		entrySem.V(groupSize);											// current group finished, so let more voters in
	}
	lock.V();
	return result;
}

TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : entrySem(group), voteSem(0), lock(1), groupSize(group), printer(printer) {
	pictureVotes = 0;
	statueVotes = 0;
	voted = 0;
}