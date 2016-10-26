#include "q3consumer.h"
#include "q3RNG.h"
#include <iostream>

Consumer::Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum ): buffer(buffer), Delay(Delay), Sentinel(Sentinel), sum(sum) {}

void Consumer::main() {
	for (;;) {
		yield(rng() % Delay);			// yield a random amount between 0 and Delay
		int elem = buffer.remove();		// remove from buffer
		if (elem == Sentinel) break;	// terminate if Sentinel value
		sum = sum + elem;
	}
}