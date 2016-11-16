#include "q3tallyVotes.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
	serving = 0;
	numVoters = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	unsigned int ticket = count;
	count++;
	while ((ticket % groupSize) != serving) {
		wait();
	}
	numVoters++;
	if (ballot == Picture) {
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (numVoters < groupSize) {
		wait();
		numVoters--;
		if (numVoters == 0) {
			serving++;
			signalAll();
		}
	} else {
		if (pictureTour > 0) {
			groupTour = Picture;
		} else {
			groupTour = Statue;
		}
		pictureTour = 0;
		numVoters--;
		signalAll();
	}
	return groupTour;
}