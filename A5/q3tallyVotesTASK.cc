#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	terminate = false;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	voteId = id;
	voteBallot = ballot;
	serverQueue.signal();
	voterQueue.wait();
	count--;
	printer.print(id, Voter::States::Unblock, count);
	return result;
}

void TallyVotes::main() {
	for (;;) {
		serverQueue.wait();
		if (terminate) break;
		count++;
		printer.print(voteId, Voter::States::Block, count);
		printer.print(voteId, Voter::States::Vote, voteBallot);
		if (voteBallot == Picture) {
			pictureTour++;
		} else {
			pictureTour--;
		}
		if (count == groupSize) {
			printer.print(voteId, Voter::States::Complete);
			result = pictureTour > 0 ? Picture : Statue;
			pictureTour = 0;
			while (!voterQueue.empty()) voterQueue.signal();
		}
	}
}

TallyVotes::~TallyVotes() {
	terminate = true;
	serverQueue.signalBlock();
}