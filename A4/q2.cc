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
	int seed;
	switch (argc) {
		case 4:
			seed = atoi(argv[3]);
			if (seed < 0) {
				usage(argv);
			}
			rng.set_seed((unsigned int) seed);
		case 3:
			groupSize = atoi(argv[2]);
		case 2:
			numVoters = atoi(argv[1]);
		case 1:
			break;
		default:
			usage(argv);
	}
	if (!(numVoters > 0 && groupSize > 0 && (numVoters % groupSize) == 0 && (groupSize % 2) == 1)) {
		usage(argv);
	}
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