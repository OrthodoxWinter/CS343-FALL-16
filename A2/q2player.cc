#include "q2player.h"
#include "q2umpire.h"
#include <iostream>

using namespace std;

Player::Player( Umpire &umpire, unsigned int Id, const PlayerList &players ): umpire(umpire), Id(Id), players(players) {}

void Player::toss(Potato &potato) {
	this->potato = &potato;
	cout << "-> " << Id << " ";
	resume();
}

void Player::main() {
	try {
		for (;;) {
			potato->countdown();
			int remaining = players.size();
			unsigned int next = rng(remaining - 1);
			if (Id == players.at(next).first) {
				next = (next + 1) % remaining;
			}
			players.at(next).second->toss(*potato);
		}
	} catch (Potato::Explode &e) {
		umpire.set(Id);
	}
}