#include "q2printer.h"
#include "q2voter.h"
#include "q2tallyVotes.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int voters) : voters(voters) {
	buffer = new State[voters];
	for (unsigned int i = 0; i < voters; i++) {
		cout.width(8);
		cout << left << "Voter" + to_string(i);
		buffer[i].type = 0;
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		cout << left << "======= ";
	}
	cout << endl;
}

Printer::~Printer() {
	delete[] buffer;
}

void Printer::flush() {
	for (unsigned int i = 0; i < voters; i++) {
		State &state = buffer[i];
		string value(1, (char) state.state);
		if (state.type == 0) {
			value = "";
		}
		if (state.type == 2) {
			value = toString(state.state, state.vote);
		}
		if (state.type == 3) {
			value = value + " " + to_string(state.numBlocked);
		}
		cout.width(8);
		cout << left << value;
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		buffer[i].type = 0;
	}
}

string Printer::toString( Voter::States state, TallyVotes::Tour vote ) {
	string value(1, (char) state);
	if (vote == TallyVotes::Tour::Picture) {
		value += " p";
	} else {
		value += " s";
	}
	return value;
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
		flush();
		string value = toString(state, vote);
		for (unsigned int i = 0; i < voters; i++) {
			cout.width(8);
			if (i == id) {
				cout << left << value;
			} else {
				cout << left << "...";
			}
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
	
	//print(id, value);
}

void Printer::print(unsigned int id, Voter::States state, unsigned int numBlocked) {
	if (buffer[id].type != 0) {
		flush();
	}
	buffer[id].state = state;
	buffer[id].numBlocked = numBlocked;
	buffer[id].type = 3;
}