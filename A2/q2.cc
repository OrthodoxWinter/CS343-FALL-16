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

//This function prints the usage and terminates
void usage(char *argv[]) {
    cout << "Usage: " << argv[0] << " number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    int numPlayers;
    int intSeed;
    uint32_t seed = getpid();                               // default the seed to pid

    switch (argc) {
        case 3:                                             // use the provided seed
            intSeed = atoi(argv[2]);
            if (intSeed < 0) usage(argv);
            seed = (uint32_t) intSeed;
        case 2:
            numPlayers = atoi(argv[1]);                     // set the number of players
            if (!(numPlayers >= 2 && numPlayers <= 20)) usage(argv);
            break;
        default:                                            // wrong number of arguments
            usage(argv);
    }

    rng.seed(seed);                                         // set the seed
    vector<pair<unsigned int, Player*>> players;            // instantiate a vector of pair<playerId, Player*>
    Umpire umpire(players);                                 // instantiate the umpire

    for (int i = 0; i < numPlayers; i++) {
        Player* player = new Player(umpire, i, players);    // create the Id Player pair and put it in the vector
        pair<unsigned int, Player*> pair(i, player);
        players.push_back(pair);
    }

    umpire.set(0);                                          // activate the umpire
}