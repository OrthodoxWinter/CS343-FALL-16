#ifndef __BINSERTSORT_H__
#define __BINSERTSORT_H__ 1

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;            // value denoting end of set
    T value;                     // communication: value being passed down/up the tree
    Binsertsort<T> *left;
    Binsertsort<T> *right;
    T nodeValue;

    void retrieveChild(Binsertsort<T> *child) {
        child->sort(Sentinel);
        for (;;) {
            value = child->retrieve();
            if (!(value == Sentinel)) {
                suspend();
            } else {
                return;
            }
        }
    }

    void main() {
        left = NULL;
        right = NULL;
        nodeValue = value;
        suspend();
        if (!(nodeValue == Sentinel)) {
            Binsertsort<T> leftChild(Sentinel);
            Binsertsort<T> rightChild(Sentinel);
            left = &leftChild;
            right = &rightChild;
            for (;;) {
                if (value == Sentinel) { 
                    break;
                }
                Binsertsort<T> *child = value < nodeValue? left : right;
                child->sort(value);
                suspend();
            }

            suspend();

            retrieveChild(left);

            value = nodeValue;
            suspend();

            retrieveChild(right);
        }
        value = Sentinel;
        suspend();
    }

  public:
    Binsertsort( T Sentinel ) : Sentinel( Sentinel ) {}
    void sort( T value ) {       // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {               // retrieve sorted value
        resume();
        return value;
    }
};

#endif