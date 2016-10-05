#ifndef __PLAYER_H__
#define __PLAYER_H__ 1

#include <vector>
#include <utility>
#include "PRNG.h"

_Coroutine Umpire;

_Coroutine Player {
	const PlayerList &players;
	Umpire &umpire;
	unsigned int eliminatePlayerId;
    void main();
  public:
    typedef std::vector< std::pair< int, Player* > > PlayerList; // container type of your choice
    Player( Umpire &umpire, unsigned int Id, const PlayerList &players );
    void toss( Potato &potato );
};

#endif