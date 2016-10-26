#ifndef __CONSUMER_H__
#define __CONSUMER_H__ 1

#include "q3buffer.h"

_Task Consumer {
	BoundedBuffer<int> &buffer;
	const int Delay;
	const int Sentinel;
	int &sum;
    void main();
  public:
    Consumer(BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum);
};

#endif