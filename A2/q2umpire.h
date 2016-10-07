#ifndef __UMPIRE_H__
#define __UMPIRE_H__ 1

#include "q2player.h"
#include "q2potato.h"

_Coroutine Umpire {
    Player::PlayerList &players;
    unsigned int eliminatedPlayerId;
    void main();
    int indexById(unsigned int Id);
  public:
    Umpire( Player::PlayerList &players );
    void set( unsigned int player );
};

#endif