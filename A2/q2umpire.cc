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
	Potato potato; 													// create potato
	int set = 1; 													// keep track of which set it is
	for (;;) {
		cout << "Set " << set << ":\tU ";
		uint32_t x = rng( players.size() - 1 ); 					// random select a player to toss to by index in the players vector
		players.at( x ).second->toss( potato );

		cout << "is eliminated" << endl;  							// at this point, a player has been eliminated and umpire has become active
		int index = indexById( eliminatedPlayerId ); 					// find the index of the eliminated player
		Player *eliminatedPlayer = players.at( index ).second; 		// remove the player from the players vector and delete
		players.erase( players.begin() + index );
		delete eliminatedPlayer;

		if ( players.size() <= 1 ) break; 							// when only one player is remaining, we break and declare winner
		potato.reset(); 											// otherwise reset potato and continue
		set++;
	}
	cout << players.at( 0 ).first << " wins the Match!" << endl;
	delete players.at( 0 ).second;
}

//This function takes a player's Id, and figure its index in the players vector
int Umpire::indexById( unsigned int Id ) {
	for (unsigned int i = 0; i < players.size(); i++) {
		if ( players.at( i ).first == Id ) return i;
	}
	return -1;
}
