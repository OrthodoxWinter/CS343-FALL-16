#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;
	printer.print(id, Voter::States::Vote, ballot);
	if (ballot == Picture) {
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count < groupSize) {
		printer.print(id, Voter::States::Block, count);
		voteQueue.wait();
		count--;
		printer.print(id, Voter::States::Unblock, count);
	} else {
		result = pictureTour > 0 ? Picture : Statue;
		count--;
		pictureTour = 0;
		printer.print(id, Voter::States::Complete);
		while (!voteQueue.empty()) voteQueue.signal();
	}
	return result;
}