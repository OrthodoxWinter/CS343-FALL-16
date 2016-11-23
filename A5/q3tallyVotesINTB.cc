#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	serving = 0;
	numVoters = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	unsigned int ticket = count;									// assigns voter a ticket.
	count++;														// increment count. Count here represents the next available ticket
	while ((ticket / groupSize) != serving) {						// ticket / groupSize indicate the group number the voter belongs in
		printer.print(id, Voter::States::Barging);					// group of this voter is not being server, which indicates barging
		wait();
	}
	printer.print(id, Voter::States::Vote, ballot);
	numVoters++;													// increment num of voters waiting to go on tour in group
	if (ballot == Picture) {										// cast vote
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (numVoters < groupSize) {									// if need more voters to form group, then wait
		printer.print(id, Voter::States::Block, numVoters);
		wait();
		numVoters--;
		printer.print(id, Voter::States::Unblock, numVoters);
	} else {
		result = pictureTour > 0 ? Picture : Statue;				// group formed, so compute result of vote
		pictureTour = 0;											// reset variables
		numVoters--;
		signalAll();												// wake up blocked voters from current group
		printer.print(id, Voter::States::Complete);
	}
	if (numVoters == 0) {										// if numVoter == 0 after decrement, then current voter is the last one in the group.
		serving++;												// start serving the next group and wake up any blocked voters belonging to the next group
		signalAll();
	}
	return result;
}

void TallyVotes::wait() {
    bench.wait();                      // wait until signalled
    while ( rand() % 5 == 0 ) {        // multiple bargers allowed
        _Accept( vote ) {              // accept barging callers
        } _Else {                      // do not wait if no callers
        } // _Accept
    } // while
}

void TallyVotes::signalAll() {
    while ( ! bench.empty() ) bench.signal(); // drain the condition
}