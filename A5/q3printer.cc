#include "q3printer.h"
#include "q3voter.h"
#include "q3tallyVotes.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int voters) : voters(voters) {
	buffer = new State[voters];
	for (unsigned int i = 0; i < voters; i++) {											// print the voters and initialize buffer to empty
		cout << "Voter" << i;
		cout << '\t';
		buffer[i].type = 0;
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		cout << "=======\t";
	}
	cout << endl;
}

Printer::~Printer() {
	delete[] buffer;
}


/*
 * Flushes the buffer by printing the states
 */
void Printer::flush() {
	for (unsigned int i = 0; i < voters; i++) {
		State &state = buffer[i];
		if (state.type != 0) {															// check state not type 0, which indicates empty
			cout << ((char) state.state);												// print the actual state character
			switch (state.type) {														// type 1 indicates no need to print vote or numBlocked
				case 1:
					break;
				case 2:																	// type 2, need to print vote
					cout << ' ' << toChar(state.vote);
					break;
				case 3:																	// type 3, need to print numBlocked
					cout << ' ' << state.numBlocked;
					break;
			}
		}
		cout << '\t';
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {											// empty buffer
		buffer[i].type = 0;
	}
}

void Printer::print( unsigned int id, Voter::States state ) {
	if (buffer[id].type != 0) {															// flush buffer if latest state for voter is not emtpy
		flush();
	}
	buffer[id].state = state;															// set the state for voter
	buffer[id].type = 1;
}

void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour vote) {
	if (state == Voter::States::Finished) {												// special logic if finished state
		for (unsigned i = 0; i < voters; i++) {
			if (buffer[i].type != 0) {													// only flush buffer it at least one voter state is not empty. This is to handle the case of 2 consecutive Finished state prints
				flush();
				break;
			}
		}
		for (unsigned int i = 0; i < voters; i++) {										// print the finish state
			if (i == id) {																// print the finish state for corresponding voter
				cout << ((char) state) << ' ' << toChar(vote);
			} else {
				cout << "...";															// all other voter prints ...
			}
			cout << '\t';
		}
		cout << endl;
	} else {																			// not printing finished state
		if (buffer[id].type != 0) {														// flush buffer if previous state is not empty
			flush();
		}
		buffer[id].state = state;														// sets latest state for voter
		buffer[id].vote = vote;
		buffer[id].type = 2;
	}
}

void Printer::print(unsigned int id, Voter::States state, unsigned int numBlocked) {
	if (buffer[id].type != 0) {
		flush();
	}
	buffer[id].state = state;
	buffer[id].numBlocked = numBlocked;
	buffer[id].type = 3;
}

/*
 * converts Tour to character
 */
char Printer::toChar(TallyVotes::Tour tour) {
	if (tour == TallyVotes::Tour::Picture) {
		return 'p';
	} else {
		return 's';
	}
}