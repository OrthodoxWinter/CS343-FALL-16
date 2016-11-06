#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	Tour result;
	entrySem.P();
	lock.P();
	if (ballot == Picture) {
		pictureVotes++;
	} else {
		statueVotes++;
	}
	printer.print(id, Voter::States::Vote, ballot);
	voted++;
	assert(voted <= groupSize);
	if (voted == groupSize) {
		assert(voteSem.counter() == (int) (-1 * (groupSize - 1)));
		printer.print(id, Voter::States::Complete);
		voteSem.V(groupSize - 1);
	} else {
		printer.print(id, Voter::States::Block, voted);
		voteSem.P(lock);
		lock.P();
		printer.print(id, Voter::States::Unblock, voted - 1);
	}
	result = pictureVotes > statueVotes ? Picture : Statue;
	voted--;
	assert(voted >= 0);
	if (voted == 0) {
		pictureVotes = 0;
		statueVotes = 0;
		entrySem.V(groupSize);
	}
	lock.V();
	return result;
}

TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : entrySem(group), voteSem(0), lock(1), groupSize(group), printer(printer) {
	pictureVotes = 0;
	statueVotes = 0;
	voted = 0;
}