#include "q2potato.h"
#include "PRNG.h"
#include <unistd.h>

Potato::Potato( unsigned int maxTicks = 10 ) {
	reset(maxTicks);
}

void Potato::reset( unsigned int maxTicks = 10 ) {
	ticks = rng(maxTicks) + 1;
}

void Potato::countdown() {
	tick--;
	if (tick == 0) _Throw Explode();
}