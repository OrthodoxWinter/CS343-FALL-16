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
		_Accept(vote);
		count--;
		printer.print(id, Voter::States::Unblock, count);
	} else {
		isPictureTour = pictureTour > 0;
		count--;
		pictureTour = 0;
		printer.print(id, Voter::States::Complete);
	}
	if (isPictureTour) {
		return Picture;
	} else {
		return Statue;
	}
}