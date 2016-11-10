#include "q2voter.h"
#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2rng.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void usage(char *argv[]) {
    cout << "Usage: " << argv[0]
     << " Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {
	unsigned int numVoters = 6, groupSize = 3;
	int seed, intGroup, intVote;
	switch (argc) {																							// read input parameters
		case 4:
			seed = atoi(argv[3]);
			if (seed < 0) {
				usage(argv);
			}
			rng.set_seed((unsigned int) seed);
		case 3:
			intGroup = atoi(argv[2]);
			if (intGroup < 0) {
				usage(argv);
			}
			groupSize = intGroup;
		case 2:
			intVote = atoi(argv[1]);
			if (intVote < 0) {
				usage(argv);
			}
			numVoters = intVote;
		case 1:
			break;
		default:
			usage(argv);
	}
	if (!((numVoters % groupSize) == 0 && (groupSize % 2) == 1)) {		// check input is valid
		usage(argv);
	}
	Printer printer(numVoters);																				// initialize objects
	TallyVotes tallier(groupSize, printer);
	Voter **voters = new Voter*[numVoters];
	for (unsigned int i = 0; i < numVoters; i++) {
		voters[i] = new Voter(i, tallier, printer);															// create voters
	}
	for (unsigned int i = 0; i < numVoters; i++) {
		delete voters[i];
	}																										// delete voters
	cout << "=================" << endl;
	cout << "All tours started" << endl;
	delete[] voters;
}