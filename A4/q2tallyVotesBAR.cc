#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>

TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : uBarrier(group), count(0), groupSize(group), printer(printer) {}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	unsigned int thisCount = count;
	unsigned int group = thisCount / groupSize;
	count++;
	if (votes.size() < (group + 1)) {
		votes.push_back(0);
	}
	if (ballot == Picture) {
		votes[group] += 1;
	} else {
		votes[group] -= 1;
	}
	printer.print(id, Voter::States::Vote, ballot);
	if (((thisCount + 1) % groupSize) != 0) printer.print(id, Voter::States::Block, waiters() + 1);
	block();
	if (((thisCount + 1) % groupSize) == 0) {
		printer.print(id, Voter::States::Complete);
	} else {
		printer.print(id, Voter::States::Unblock, waiters());
	}
	if (votes[group] > 0) {
		return Picture;
	} else {
		return Statue;
	}
}