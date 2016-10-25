#ifndef __BUFFER_H__
#define __BUFFER_H__ 1

#include <list>
#include <assert.h>

template<typename T> class BoundedBuffer {
	std::list<T> buffer;   // a linked list which backs BoundedBuffer
	const unsigned int size;   // keeps track of the max size of the buffer
	uOwnerLock lock;
	uCondLock notEmpty;
	uCondLock notFull;

#ifdef NOBUSY
    bool preventBarge;      //flag variable indicate if barging should be prevented
    uCondLock barge;
#endif

  public:
    BoundedBuffer( const unsigned int size = 10 ): size(size) {
#ifdef NOBUSY
        preventBarge = false;   // don't prevent barging in the beginning
#endif
    }

#ifdef BUSY
    void insert( T elem ) {
    	lock.acquire();    //ensure mutex
    	while (buffer.size() == size) {    //if buffer is full, then wait. Since bargning can occur, must be a while loop
    		notFull.wait(lock);
    	}
        assert(buffer.size() < size);
    	buffer.push_back(elem);            // adds element to buffer
    	notEmpty.signal();                 // signal that buffer is not empty
    	lock.release();
    }
    T remove() {
    	lock.acquire();            //ensure mutex
    	while (buffer.size() == 0) {   // if buffer is empty, then wait. Since bargning can occur, must be a while loop
    		notEmpty.wait(lock);
    	}
        assert(buffer.size() > 0);
    	T elem = buffer.front();       // remove fron buffer
        buffer.pop_front();
    	notFull.signal();              // signal buffer not full
    	lock.release();
    	return elem;               // return element
    }
#endif

#ifdef NOBUSY
    void insert( T elem ) {
        lock.acquire();
        if (preventBarge) {         // check if barging is being prevented. If so, then every newly arriving insert must wait.
            barge.wait(lock);
            if (barge.empty()) {
                preventBarge = false; // need to allow barging, because otherwise all future operations will wait on barge with nobody waking them up
            }
        }
        if (buffer.size() == size) {
            barge.signal();
            notFull.wait(lock);
        }
        assert(buffer.size() < size);
        buffer.push_back(elem);
        if (!notEmpty.empty()) {
            preventBarge = true; //prevent barging, so that other remove can't barge in before the signaled one, which would violate the assert
            notEmpty.signal();
        } else {
            if (!barge.empty()) {
                preventBarge = true; //prevent barging. Otherwise this could cause multiple insert/remove to be signalled. In that scenario, it's possible for one insert/remove to run and allow barge before the rest wake up.
                barge.signal();
            } else {
                preventBarge = false; // need to allow barging, because otherwise all future operations will wait on barge with nobody waking them up
            }
        }
        lock.release();
    }

    T remove() {
        lock.acquire();
        if (preventBarge) {
            barge.wait(lock);
            if (barge.empty()) {
                preventBarge = false;
            }
        }
        if (buffer.size() == 0) {
            barge.signal();
            notEmpty.wait(lock);
        }
        assert(buffer.size() > 0);
        T elem = buffer.front();
        buffer.pop_front();
        if (!notFull.empty()) {
            preventBarge = true;
            notFull.signal();
        } else {
            if (!barge.empty()) {
                preventBarge = true;
                barge.signal();
            } else {
                preventBarge = false;
            }
        }
        lock.release();
        return elem;
    }
#endif
};

#endif