#include "q2potato.h"
#include <unistd.h>
#include <iostream>

using namespace std;

PRNG rng;

//constructor which specifies a max tick
Potato::Potato( unsigned int maxTicks ) {
	reset( maxTicks );
}

//reset the potato's ticks
void Potato::reset( unsigned int maxTicks ) {
	ticks = rng( maxTicks - 1 ) + 1; 				//randomly generate ticks to be [1, maxTicks]
	cout << "  POTATO goes off after " << ticks << " toss";
	if ( ticks > 1 ) { 								// gramatical correctness in output
		cout << "es";
	}
	cout << endl;
}

//this function decrements ticks and throw exception if it gets to 0
void Potato::countdown() {
	ticks--;
	if ( ticks <= 0 ) _Throw Explode();
}