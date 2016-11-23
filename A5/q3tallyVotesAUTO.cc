#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	groupFormed = false;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;															// increment count. Count represent current num of voters waiting to go on tour
	printer.print(id, Voter::States::Vote, ballot);
	if (ballot == Picture) {											// cast vote
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count == groupSize) {											// enough voters to form a group
		result = pictureTour > 0 ? Picture : Statue;					// compute result of vote
		pictureTour = 0;												// reset variables
		count--;
		groupFormed = true;												// indicate that group is formed
		printer.print(id, Voter::States::Complete);
	} else {
		groupFormed = false;											// indicate group not formed
		WAITUNTIL(														// wait until group is formed. The reason we don't wait for count == groupSize is because count gets decremented
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