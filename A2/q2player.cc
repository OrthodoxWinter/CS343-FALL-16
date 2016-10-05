#include "q2player.h"

Player::Player( Umpire &umpire, unsigned int Id, const PlayerList &players ): umpire(umpire), Id(Id), players(players) {}

void Player::toss(Potato &potato) {
	this.potato = potato;
	resume();
}

void Player::main() {
	try {
		for (;;) {
			potato.countdown();
			int remaining = players.size();
			int next = rng(remaining)
			if (next == players.at(next).first) {
				next = (next + 1) % players.remaining;
			}
			players.at(next).second->toss(potato);
		}
	} catch (Explode &e) {
		umpire.set(id);
	}
}