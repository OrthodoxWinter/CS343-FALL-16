#ifndef __BUFFER_H__
#define __BUFFER_H__ 1

#include <list>
#include <assert.h>

template<typename T> class BoundedBuffer {
	std::list<T> buffer;
	const unsigned int size;
	uOwnerLock lock;
	uCondLock notEmpty;
	uCondLock notFull;

#ifdef NOBUSY
    bool preventBarge;
    uCondLock barge;
#endif

  public:
    BoundedBuffer( const unsigned int size = 10 ): size(size) {
#ifdef NOBUSY
        preventBarge = false;
#endif
    }

#ifdef BUSY
    void insert( T elem ) {
    	lock.acquire();
    	while (buffer.size() == size) {
    		notFull.wait(lock);
    	}
        assert(buffer.size() < size);
    	buffer.push_back(elem);
    	notEmpty.signal();
    	lock.release();
    }
    T remove() {
    	lock.acquire();
    	while (buffer.size() == 0) {
    		notEmpty.wait(lock);
    	}
        assert(buffer.size() > 0);
    	T elem = buffer.front();
        buffer.pop_front();
    	notFull.signal();
    	lock.release();
    	return elem;
    }
#endif

#ifdef NOBOSU
    void insert( T elem ) {
        lock.acquire();
        if (preventBarge) {
            barge.wait(lock);
        }
        if (buffer.size() == size) {
            notFull.wait(lock);
        }
        assert(buffer.size() < size);
        buffer.push_back(elem);
        if (!notEmpty.empty()) {
            preventBarge = true;
            notEmpty.signal();
        } else {
            if (!barge.empty()) {
                preventBarge = true;
                barge.signal();
            } else {
                preventBarge = false;
            }
        }
        lock.release();
    }
    T remove() {
        lock.acquire();
        if (buffer.size() == 0) {
            notEmpty.wait(lock);
        }
        assert(buffer.size() > 0);
        T elem = buffer.front();
        buffer.pop_front();
        notFull.signal();
        lock.release();
        return elem;
    }
#endif
};

#endif