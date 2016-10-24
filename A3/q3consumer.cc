#include "q3consumer.h"
#include "q3RNG.h"
#include <iostream>

Consumer::Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum ): buffer(buffer), Delay(Delay), Sentinel(Sentinel), sum(sum) {}

void Consumer::main() {
	for (;;) {
		yield(rng() % Delay);
		int elem = buffer.remove();
		if (elem == Sentinel) break;
		sum = sum + elem;
	}
}