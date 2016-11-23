#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	terminate = false;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	voteId = id;													// copy the parameters. These variables are meant as input for main
	voteBallot = ballot;
	serverQueue.signal();											// wake up main
	voterQueue.wait();												// block
	count--;														// woke up, decrement count, print and return result
	printer.print(id, Voter::States::Unblock, count);
	return result;
}

void TallyVotes::main() {
	for (;;) {
		serverQueue.wait();											// block
		if (terminate) break;										// unblocked due to termination, so break out of loop
		count++;													// not terminate, so process vote from voter. Start by increment count, which represent num of voters in group currently
		printer.print(voteId, Voter::States::Vote, voteBallot);
		printer.print(voteId, Voter::States::Block, count);			// print block message for the voter
		if (voteBallot == Picture) {								// cast vote
			pictureTour++;
		} else {
			pictureTour--;
		}
		if (count == groupSize) {									// check if group formed. If not, then block until next voter
			printer.print(voteId, Voter::States::Complete);			// group formed, so compute result of vote
			result = pictureTour > 0 ? Picture : Statue;
			pictureTour = 0;										// reset variables
			while (!voterQueue.empty()) voterQueue.signal();		// wake up blocked voter
		}
	}
}

TallyVotes::~TallyVotes() {
	terminate = true;												// destructor called, indicate to main that it is terminated
	serverQueue.signalBlock();										// singalBlock to allow main to wake up and break out of loop
}