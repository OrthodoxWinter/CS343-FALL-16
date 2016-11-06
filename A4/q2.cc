#include "q2voter.h"
#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2rng.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void uMain::main() {
	unsigned int numVoters, groupSize, seed;
	numVoters = atoi(argv[1]);
	groupSize = atoi(argv[2]);
	seed = atoi(argv[3]);
	rng.set_seed(seed);
	Printer printer(numVoters);
	TallyVotes tallier(groupSize, printer);
	Voter **voters = new Voter*[numVoters];
	for (unsigned int i = 0; i < numVoters; i++) {
		voters[i] = new Voter(i, tallier, printer);
	}
	for (unsigned int i = 0; i < numVoters; i++) {
		delete voters[i];
	}
	cout << "=================" << endl;
	cout << "All tours started" << endl;
	delete[] voters;
}