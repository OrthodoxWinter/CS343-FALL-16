#include "q2player.h"
#include "q2umpire.h"
#include "q2potato.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void usage(char *argv[]) {
    cout << "Usage: " << argv[0] << " number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    int numPlayers;
    int intSeed;
    uint32_t seed = getpid();

    switch (argc) {
        case 3:
            intSeed = atoi(argv[2]);
            if (intSeed < 0) usage(argv);
            seed = (uint32_t) intSeed;
        case 2:
            numPlayers = atoi(argv[1]);
            if (!(numPlayers >= 2 && numPlayers <= 20)) usage(argv);
            break;
        default:
            usage(argv);
    }

    rng.seed(seed);
    vector<pair<unsigned int, Player*>> players;
    Umpire umpire(players);

    for (int i = 0; i < numPlayers; i++) {
        Player* player = new Player(umpire, i, players);
        pair<unsigned int, Player*> pair(i, player);
        players.push_back(pair);
    }

    umpire.set(0);
}