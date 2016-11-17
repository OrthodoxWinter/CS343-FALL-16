#include "q3printer.h"
#include "q3voter.h"
#include "q3tallyVotes.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int voters) : voters(voters) {
	buffer = new State[voters];
	for (unsigned int i = 0; i < voters; i++) {
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

void Printer::flush() {
	for (unsigned int i = 0; i < voters; i++) {
		State &state = buffer[i];
		if (state.type != 0) {
			cout << ((char) state.state);
			switch (state.type) {
				case 1:
					break;
				case 2:
					cout << ' ' << toChar(state.vote);
					break;
				case 3:
					cout << ' ' << state.numBlocked;
					break;
			}
		}
		cout << '\t';
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		buffer[i].type = 0;
	}
}

void Printer::print( unsigned int id, Voter::States state ) {
	if (buffer[id].type != 0) {
		flush();
	}
	buffer[id].state = state;
	buffer[id].type = 1;
}

void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour vote) {
	if (state == Voter::States::Finished) {
		for (unsigned i = 0; i < voters; i++) {
			if (buffer[i].type != 0) {
				flush();
				break;
			}
		}
		for (unsigned int i = 0; i < voters; i++) {
			if (i == id) {
				cout << ((char) state) << ' ' << toChar(vote);
			} else {
				cout << "...";
			}
			cout << '\t';
		}
		cout << endl;
	} else {
		if (buffer[id].type != 0) {
			flush();
		}
		buffer[id].state = state;
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

char Printer::toChar(TallyVotes::Tour tour) {
	if (tour == TallyVotes::Tour::Picture) {
		return 'p';
	} else {
		return 's';
	}
}