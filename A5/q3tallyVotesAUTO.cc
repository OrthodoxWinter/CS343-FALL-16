#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	groupFormed = false;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;
	printer.print(id, Voter::States::Vote, ballot);
	if (ballot == Picture) {
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count == groupSize) {
		result = pictureTour > 0 ? Picture : Statue;
		pictureTour = 0;
		count--;
		groupFormed = true;
		printer.print(id, Voter::States::Complete);
	} else {
		groupFormed = false;
		WAITUNTIL(
			groupFormed == true,
			printer.print(id, Voter::States::Block, count),
			{
				count--;
				printer.print(id, Voter::States::Unblock, count);
			}
		);
		
	}
	RETURN(result);
}