#include "q2umpire.h"
#include <iostream>

using namespace std;

Umpire::Umpire( Player::PlayerList &players ): players(players) {}

void Umpire::set( unsigned int Id ) {
	eliminatedPlayerId = Id;
	resume();
}

void Umpire::main() {
	unsigned int initial = players.size();
	cout << initial << " players in the match" << endl;
	Potato potato;
	int set = 1;
	for (;;) {
		cout << "Set " << set << ":\tU ";
		uint32_t x = rng(players.size() - 1);
		players.at(x).second->toss(potato);

		cout << "is eliminated" << endl;
		int index = indexById(eliminatedPlayerId);
		Player *eliminatedPlayer = players.at(index).second;
		players.erase(players.begin() + index);
		delete eliminatedPlayer;
		if (players.size() <= 1) break;
		potato.reset();
		set++;
	}
	cout << players.at(0).first << " wins the Match!" << endl;
	delete players.at(0).second;
}

int Umpire::indexById(unsigned int Id) {
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players.at(i).first == Id) return i;
	}
	return -1;
}
