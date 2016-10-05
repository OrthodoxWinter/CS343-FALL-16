#include "q2umpire.h"
#include "potato.h"

Umpire::Umpire( Player::PlayerList &players ): players(players), potato(players.size()) {
	resume();
}

void Umpire::set( unsigned int Id ) {
	eliminatedPlayerId = Id;
}

void Umpire::main() {
	for (int i = 0; i < players.size() - 1; i++) {
		players.at(rng(players.size())).second->toss(potato);
		int index = indexById(eliminatedPlayerId);
		players.erase(players.begin() + index);
	}
	if (size == 0) {
		//?
	} else {
		//declare winner
	}
}

int Umpire::indexById(unsigned int Id) {
	for (int i = 0; i < players.size(); i++) {
		if (players.at(i).first == Id) return i;
	}
	return -1;
}
