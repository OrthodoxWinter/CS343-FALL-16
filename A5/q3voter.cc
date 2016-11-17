#include "q3voter.h"
#include "q3rng.h"
#include "q3printer.h"

void Voter::main() {
	yield(rng() % 20);
	printer.print(id, Start);
	yield(1);
	TallyVotes::Tour tour = voteTallier.vote(id, (rng() % 2) == 0 ? TallyVotes::Tour::Picture : TallyVotes::Tour::Statue);
	yield(1);
	printer.print(id, Finished, tour);
}

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer) : id(id), voteTallier(voteTallier), printer(printer) {}