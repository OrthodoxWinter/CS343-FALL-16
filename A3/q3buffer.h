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
    bool preventInsertBarge;
    uCondLock insertBarge;

    bool preventRemoveBarge;
    uCondLock removeBarge;
#endif

  public:
    BoundedBuffer( const unsigned int size = 10 ): size(size) {
#ifdef NOBUSY
        preventInsertBarge = false;
        preventRemoveBarge = false;
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

#ifdef NOBUSY
    void insert( T elem ) {
        lock.acquire();
        if (preventInsertBarge) {
            insertBarge.wait(lock);
            preventInsertBarge = false;
        }
        if (buffer.size() == size) {
            notFull.wait(lock);
            preventInsertBarge = false;
        }
        assert(buffer.size() < size);
        buffer.push_back(elem);
        if (!notEmpty.empty()) {
            preventRemoveBarge = true;
            notEmpty.signal();
        } else {
            if (!removeBarge.empty()) {
                preventRemoveBarge = true;
                removeBarge.signal();
            } else {
                preventRemoveBarge = false;
            }
        }
        lock.release();
    }

    T remove() {
        lock.acquire();
        if (preventRemoveBarge) {
            removeBarge.wait(lock);
            preventRemoveBarge = false;
        }
        if (buffer.size() == 0) {
            notEmpty.wait(lock);
            preventRemoveBarge = false;
        }
        assert(buffer.size() > 0);
        T elem = buffer.front();
        buffer.pop_front();
        if (!notFull().empty()) {
            preventInsertBarge = true;
            notFull.signal();
        } else {
            if (!insertBarge.empty()) {
                preventInsertBarge = true;
                insertBarge.signal();
            } else {
                preventInsertBarge = false;
            }
        }
        lock.release();
        return elem;
    }
#endif
};

#endif