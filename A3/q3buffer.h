#ifndef __BUFFER_H__
#define __BUFFER_H__ 1

#include <list>
#include <assert.h>

template<typename T> class BoundedBuffer {
	std::list<T> buffer;                   // a linked list which backs BoundedBuffer
	const unsigned int size;               // keeps track of the max size of the buffer
	uOwnerLock lock;
	uCondLock notEmpty;
	uCondLock notFull;

#ifdef NOBUSY
    bool preventBarge;                      //flag variable indicate if barging should be prevented
    uCondLock barge;
#endif

  public:
    BoundedBuffer(const unsigned int size = 10): size(size) {
#ifdef NOBUSY
        preventBarge = false;               // don't prevent barging in the beginning
#endif
    }

#ifdef BUSY
    void insert(T elem) {
    	lock.acquire();                    //ensure mutex
    	while (buffer.size() == size) {    //if buffer is full, then wait. Since bargning can occur, must be a while loop
    		notFull.wait(lock);
    	}
        assert(buffer.size() < size);
    	buffer.push_back(elem);            // adds element to buffer
    	notEmpty.signal();                 // signal that buffer is not empty
    	lock.release();
    }
    T remove() {
    	lock.acquire();                    //ensure mutex
    	while (buffer.size() == 0) {       // if buffer is empty, then wait. Since bargning can occur, must be a while loop
    		notEmpty.wait(lock);
    	}
        assert(buffer.size() > 0);
    	T elem = buffer.front();           // remove fron buffer
        buffer.pop_front();
    	notFull.signal();                  // signal buffer not full
    	lock.release();
    	return elem;                       // return element
    }
#endif

#ifdef NOBUSY

    /*
     * check if barging is prevented and wait if it is
     */
    void bargeWait() {
        if (preventBarge) {                // check if barging is being prevented. If so, then every newly arriving insert must wait.
            barge.wait(lock);
            if (barge.empty()) {
                preventBarge = false;      // need to reset barging flag, because otherwise all future operations will wait on barge with nobody waking them up
            }
        }
    }

    /*
     * try to signal the specified condition lock, which is expected to be either notFull or notEmpty. If both are empty, then signal from barge cond lock
     */
    void signal(uCondLock &cond) {
        if (!cond.empty()) {
            preventBarge = true;           //prevent barging, so that other remove can't barge in before the signaled one, which would violate the assert
            cond.signal();
        } else {
            if (!barge.empty()) {
                preventBarge = true;       //prevent barging. Otherwise this could cause multiple insert/remove to be signalled. In that scenario, it's possible for one insert/remove to run and allow barge at the end before the other gets to run
                barge.signal();
            } else {
                preventBarge = false;      // need to allow barging, because otherwise all future operations will wait on barge with nobody waking them up
            }
        }
    }

    void insert(T elem) {
        lock.acquire();                    //ensure mutex
        bargeWait();                       //wait if no barging
        if (buffer.size() == size) {       //wait if buffer is full
            barge.signal();                //need to signal barge cond lock because it's possible all other remove are waiting on barge. If we don't wake them up we'll sleep forever
            notFull.wait(lock);
        }
        assert(buffer.size() < size);
        buffer.push_back(elem);
        signal(notEmpty);                  //signal notEmpty
        lock.release();
    }

    T remove() {
        lock.acquire();                     //ensure mutex
        bargeWait();                        //wait if no barging
        if (buffer.size() == 0) {           //wait if buffer is empty
            barge.signal();                 //need to signal barge cond lock because it's possible all other insert are waiting on barge. If we don't wake them up we'll sleep forever
            notEmpty.wait(lock);
        }
        assert(buffer.size() > 0);
        T elem = buffer.front();
        buffer.pop_front();
        signal(notFull);                    //signal notFull
        lock.release();
        return elem;
    }
#endif
};

#endif