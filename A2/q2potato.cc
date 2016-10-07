#include "q2potato.h"
#include <unistd.h>
#include <iostream>

using namespace std;

PRNG rng;

Potato::Potato( unsigned int maxTicks ) {
	reset(maxTicks);
}

void Potato::reset( unsigned int maxTicks ) {
	ticks = rng(maxTicks - 1) + 1;
	cout << "Potato will explode after " << ticks << " ticks" << endl;
}

void Potato::countdown() {
	ticks--;
	cout << "tick " << ticks << endl;
	if (ticks <= 0) _Throw Explode();
}