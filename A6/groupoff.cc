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
		//break on destructor
		_Accept(~Groupoff) {
			break;
		} _Else {
			yield(groupoffDelay);
			// randomly select a future
			unsigned int selection = rng() % numAvailableFutures;
			WATCard::FWATCard toGift = futureCards[selection];
			// swap the future we just selected into the last position
			futureCards[selection] = futureCards[numAvailableFutures - 1];
			futureCards[numAvailableFutures - 1] = toGift;
			// decrement numAvailableFutures, thus marking the future we just selected as unavailable
			numAvailableFutures--;
			// create new card with sodaCost in it, and deliver into future
			WATCard *card = new WATCard();
			card->deposit(sodaCost);
			printer.print(Printer::Kind::Groupoff, 'D', sodaCost);
			toGift.delivery(card);
			// All giftcards have been delivered, so stop
			if (numAvailableFutures == 0) break;
		}
	}
	printer.print(Printer::Kind::Groupoff, 'F');
}