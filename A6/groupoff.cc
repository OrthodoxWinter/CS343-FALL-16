#include "rng.h"
#include "groupoff.h"

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
	//Initialize array
	futureCards = new WATCard::FWATCard[numStudents];
	nextFuture = 0;
}

Groupoff::~Groupoff() {
	delete[] futureCards;
}

WATCard::FWATCard Groupoff::giftCard() {
	WATCard::FWATCard future = futureCards[nextFuture];
	nextFuture++;
	return future;
}

void Groupoff::main() {
	printer.print(Printer::Kind::Groupoff, 'S');
	unsigned int numAvailableFutures = numStudents;
	//begins by accepting a call from each student to obtain a future card
	for (unsigned int i = 0; i < numStudents; i++) {
		_Accept(giftCard);
	}
	for (;;) {
		_Accept(~Groupoff) {
			break;
		} _Else {
			yield(groupoffDelay);
			unsigned int selection = rng() % numAvailableFutures;				// randomly select a future
			WATCard::FWATCard toGift = futureCards[selection];
			futureCards[selection] = futureCards[numAvailableFutures - 1];		// swap the future we just selected into the last position
			futureCards[numAvailableFutures - 1] = toGift;
			numAvailableFutures--;												// decrement numAvailableFutures, thus marking the future we just selected as unavailable
			WATCard *card = new WATCard();										// create new card with sodaCost in it, and deliver into future
			card->deposit(sodaCost);
			printer.print(Printer::Kind::Groupoff, 'D', sodaCost);
			toGift.delivery(card);
			if (numAvailableFutures == 0) break;								// All giftcards have been delivered, so stop
		}
	}
	printer.print(Printer::Kind::Groupoff, 'F');
}