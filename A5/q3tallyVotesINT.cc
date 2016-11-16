#include "q3tallyVotes.h"

TallyVotes::TallyVotes(unsigned int group, Printer &printer): groupSize(group), printer(printer) {
	count = 0;
	pictureTour = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	count++;
	if (ballot == Picture) {
		pictureTour++;
	} else {
		pictureTour--;
	}
	if (count < groupSize) {
		voteQueue.wait();
	} else {
		if (pictureTour > 0) {
			groupTour = Picture;
		} else {
			groupTour = Statue;
		}
		count = 0;
		pictureTour = 0;
	}
	voteQueue.signal();
	return groupTour;
}