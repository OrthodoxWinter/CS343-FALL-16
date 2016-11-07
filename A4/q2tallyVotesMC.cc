#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"
#include <cassert>
#include <iostream>

using namespace std;

TallyVotes::TallyVotes(unsigned int group, Printer &printer) : groupSize(group), printer(printer) {
	count = 0;
	voted = 0;
	resultRead = 0;
	pictureVotes = 0;
	statueVotes = 0;
	noBarge = false;
}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ) {
	Tour result;
	lock.acquire();
	if (noBarge) {
		printer.print(id, Voter::States::Barging);
		bargeQueue.wait(lock);
	}
	if (count == groupSize) {
		printer.print(id, Voter::States::Barging);
		entryQueue.wait(lock);
	}
	assert(count < groupSize);
	assert(resultRead == 0);
	count++;
	if (count < groupSize) {
		if (!entryQueue.empty()) {
			entryQueue.signal();
			noBarge = true;
		} else if (!bargeQueue.empty()) {
			bargeQueue.signal();
			noBarge = true;
		} else {
			noBarge = false;
		}
	}
	if (ballot == Picture) {
		pictureVotes++;
	} else {
		statueVotes++;
	}
	assert(pictureVotes <= groupSize);
	assert(statueVotes <= groupSize);
	printer.print(id, Voter::States::Vote, ballot);
	voted++;
	assert(voted <= groupSize);
	if (voted == groupSize) {
		voteQueue.broadcast();
		printer.print(id, Voter::States::Complete);
	} else {
		printer.print(id, Voter::States::Block, voted);
		voteQueue.wait(lock);
		printer.print(id, Voter::States::Unblock, groupSize - resultRead - 1);
	}
	result = pictureVotes > statueVotes ? Picture : Statue;
	resultRead++;
	assert(resultRead <= groupSize);
	if (resultRead == groupSize) {
		count = 0;
		pictureVotes = 0;
		statueVotes = 0;
		resultRead = 0;
		voted = 0;
		if (!entryQueue.empty()) {
			entryQueue.signal();
			noBarge = true;
		} else if (!bargeQueue.empty()) {
			bargeQueue.signal();
			noBarge = true;
		} else {
			noBarge = false;
		}
	}
	lock.release();
	return result;
}