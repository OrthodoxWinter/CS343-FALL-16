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
	unsigned int ticket = count;
	count++;
	if ((ticket / groupSize) != serving) {
		printer.print(id, Voter::States::Barging);
		while ((ticket / groupSize) != serving) {
			wait();
		}
	}
	printer.print(id, Voter::States::Vote, ballot);
	numVoters++;
	if (ballot == Picture) {
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (numVoters < groupSize) {
		printer.print(id, Voter::States::Block, numVoters);
		wait();
		numVoters--;
		printer.print(id, Voter::States::Unblock, numVoters);
		if (numVoters == 0) {
			serving++;
			signalAll();
		}
	} else {
		result = pictureTour > 0 ? Picture : Statue;
		pictureTour = 0;
		numVoters--;
		signalAll();
		printer.print(id, Voter::States::Complete);
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