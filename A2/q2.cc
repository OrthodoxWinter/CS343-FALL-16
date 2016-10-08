#include "q2player.h"
#include "q2umpire.h"
#include "q2potato.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <stdlib.h>

using namespace std;

void uMain::main() {

    istream *infile = &cin;                                                             // default input is cin

    int numPlayers = atoi(argv[1]);
    uint32_t seed = (uint32_t) atoi(argv[2]);

    rng.seed(seed);
    vector<pair<unsigned int, Player*>> players;
    Umpire umpire(players);

    for (int i = 0; i < numPlayers; i++) {
        Player* player = new Player(umpire, i, players);
        pair<unsigned int, Player*> pair(i, player);
        players.push_back(pair);
    }

    umpire.set(0);

    if ( infile != &cin ) delete infile;                                                // close file if applicable
}