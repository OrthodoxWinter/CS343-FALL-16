#include <list>

template<typename T> class BoundedBuffer {
	list<T> buffer;
	const unsigned int size;
	uOwnerLock lock;
	uCondLock notEmpty;
	uCondLock notFull;
  public:
    BoundedBuffer( const unsigned int size = 10 ): size(size) {}
    void insert( T elem ) {
    	lock.acquire();
    	while (buffer.size == size) {
    		notFull.wait(lock);
    	}
    	buffer.push_back(elem);
    	notEmpty.signal();
    	lock.release();
    }
    T remove() {
    	lock.acquire();
    	while (buffer.size == 0) {
    		notEmpty.wait(lock);
    	}
    	T elem = buffer.pop_front();
    	notFull.signal();
    	lock.release();
    	return elem;
    }
};