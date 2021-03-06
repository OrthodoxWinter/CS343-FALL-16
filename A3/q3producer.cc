#include "q3producer.h"
#include "q3RNG.h"

Producer::Producer(BoundedBuffer<int> &buffer, const int Produce, const int Delay): buffer(buffer), Produce(Produce), Delay(Delay) {};

void Producer::main() {
	for (int i = 1; i <= Produce; i++) {
		yield(rng() % Delay);			//yield a random amount between 0 and Delay - 1
		buffer.insert(i);				//insert into buffer
	}
}