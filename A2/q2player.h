#ifndef __PLAYER_H__
#define __PLAYER_H__ 1

#include <vector>
#include <utility>
#include "q2potato.h"

_Coroutine Umpire;

_Coroutine Player {
  public:
    typedef std::vector< std::pair< unsigned int, Player* > > PlayerList; // PlayersList is chosen to be a vector of pairs, where the pair is a Player's Id and the Player pointer.
    Player( Umpire &umpire, unsigned int Id, const PlayerList &players );
    void toss( Potato &potato );
  private:
  	Umpire &umpire;
    unsigned int Id;
	  const PlayerList &players;
	  Potato *potato;
    void main();
};

#endif