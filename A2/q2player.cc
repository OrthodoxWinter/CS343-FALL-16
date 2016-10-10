#include "q2player.h"
#include "q2umpire.h"
#include <iostream>

using namespace std;

Player::Player( Umpire &umpire, unsigned int Id, const PlayerList &players ): umpire( umpire ), Id( Id ), players( players ) {}

//This function is called when the potato is to be tossed to this player
void Player::toss( Potato &potato ) {
	this->potato = &potato;
	cout << "-> " << Id << " ";
	resume();
}

void Player::main() {
	try {
		for (;;) {
			potato->countdown(); 							// countdown potato
			int remaining = players.size();
			unsigned int next = rng( remaining - 1 ); 		// choose a new player to toss the potato to
			if ( Id == players.at( next ).first ) {			// choose the next player if randomly selects itself
				next = ( next + 1 ) % remaining;
			}
			players.at( next ).second->toss( *potato );		// activate the new player
		}
	} catch ( Potato::Explode ) {
		umpire.set( Id ); 									// if potato explodes, then activate umpire
	}
}