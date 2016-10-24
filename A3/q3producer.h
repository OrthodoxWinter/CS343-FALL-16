#ifndef __PRODUCER_H__
#define __PRODUCER_H__ 1

#include "q3buffer.h"

_Task Producer {
	BoundedBuffer<int> &buffer;
	const int Produce;
	const int Delay;
    void main();
  public:
    Producer( BoundedBuffer<int> &buffer, const int Produce, const int Delay );
};

#endif