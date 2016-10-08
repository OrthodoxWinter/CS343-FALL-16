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
	cout << "  POTATO goes off after " << ticks << " toss";
	if (ticks > 1) {
		cout << "es";
	}
	cout << endl;
}

void Potato::countdown() {
	ticks--;
	if (ticks <= 0) _Throw Explode();
}