#include "q2printer.h"
#include "q2voter.h"
#include "q2tallyVotes.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int voters) : voters(voters) {
	for (unsigned int i = 0; i < voters; i++) {
		buffer.push_back("");
		cout.width(8);
		cout << left << "Voter" + to_string(i);
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		cout << left << "======= ";
	}
	cout << endl;
}

void Printer::flush(string value) {
	for (unsigned int i = 0; i < voters; i++) {
		cout.width(8);
		cout << left << buffer[i];
	}
	cout << endl;
	for (unsigned int i = 0; i < voters; i++) {
		buffer[i] = value;
	}
}

void Printer::print( unsigned int id, std::string state) {
	
	string value = buffer[id];
	if (value != "" && value != "..." && value != state) {
		flush();
	}
	buffer[id] = state;
	
	//cout << "state " << state << " for voter" << id << endl;
}

void Printer::print( unsigned int id, Voter::States state ) {
	string value(1, (char) state);
	print(id, value);
}

void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour vote) {
	string value(1, (char) state);
	if (vote == TallyVotes::Tour::Picture) {
		value += " p";
	} else {
		value += " s";
	}
	
	if (state == Voter::States::Finished) {
		flush();
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
		print(id, value);
	}
	
	//print(id, value);
}

void Printer::print(unsigned int id, Voter::States state, unsigned int numBlocked) {
	string value(1, (char) state);
	print(id, value + " " + to_string(numBlocked));
}