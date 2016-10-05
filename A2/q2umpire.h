#ifndef __UMPIRE_H__
#define __UMPIRE_H__ 1

#include "q2player.h"

_Coroutine Umpire {
    Player::PlayerList &players;
    Potato potato;
    void main();
    unsigned int indexById(unsigned int Id);
  public:
    Umpire( Player::PlayerList &players );
    void set( unsigned int player );
};

#endif