#include "q2umpire.h"
#include <iostream>

using namespace std;

Umpire::Umpire( Player::PlayerList &players ): players(players) {}

void Umpire::set( unsigned int Id ) {
	eliminatedPlayerId = Id;
	resume();
}

void Umpire::main() {
	Potato potato;
	unsigned int initial = players.size();
	cout << initial << " players" << endl;
	for (unsigned int i = 0; i < initial - 1; i++) {
		uint32_t x = rng(players.size() - 1);
		cout << "generated " << x << endl;
		players.at(x).second->toss(potato);
		int index = indexById(eliminatedPlayerId);
		cout << "player id: " << eliminatedPlayerId << " with position " << index << " is eliminated" << endl;
		Player *eliminatedPlayer = players.at(index).second;
		players.erase(players.begin() + index);
		delete eliminatedPlayer;
		potato.reset();
	}
	delete players.at(0).second;
	cout << "umpire finished" << endl;
}

int Umpire::indexById(unsigned int Id) {
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players.at(i).first == Id) return i;
	}
	return -1;
}
