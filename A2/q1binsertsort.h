#ifndef __BINSERTSORT_H__
#define __BINSERTSORT_H__ 1

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;                                                       // value denoting end of set
    T value;                                                                // communication: value being passed down/up the tree
    Binsertsort<T> *left;                                                   // left child
    Binsertsort<T> *right;                                                  // right child
    T nodeValue;                                                            // node value

    /*
     * This function retrieve all the values in a child tree until 
     * a Sentinel value is returned, at which point it returns.
     * Every time a non-Sentinel value is encountered, this function suspends
     * the coroutine
     */
    void retrieveChild( Binsertsort<T> *child ) {
        child->sort( Sentinel );                                              //signal end of input to child
        for ( ;; ) {
            value = child->retrieve();
            if ( !( value == Sentinel ) ) {
                suspend();
            } else {
                return;
            }
        }
    }

    void main() {
        left = NULL;
        right = NULL;
        nodeValue = value;                                                  // set the node value on first resume
        suspend();
        if ( !( nodeValue == Sentinel ) ) {                                     // on second resume, check if the node value is Sentinel. If yes, we set value to Sentinel and terminate
            Binsertsort<T> leftChild( Sentinel );                             //node value is not Sentinel, so we create left and right child, and prepare to read more values
            Binsertsort<T> rightChild( Sentinel );
            left = &leftChild;
            right = &rightChild;
            for ( ;; ) {                                                      // read values passed in by sort
                if ( value == Sentinel ) {                                    //stop when a Sentinel value is encountered
                    break;
                }
                Binsertsort<T> *child = value < nodeValue? left : right;    // give value to the correct child
                child->sort( value );
                suspend();
            }

            suspend();                                                      // this suspend is for the Sentinel value

            retrieveChild( left );                                            // retrieve all values of left child

            value = nodeValue;                                              // retrieve value of the current node
            suspend();

            retrieveChild( right );                                           // retrieve all values of right child
        }
        value = Sentinel;                                                   // give back Sentinel to indicate the end
    }

  public:
    Binsertsort( T Sentinel ) : Sentinel( Sentinel ) {}
    void sort( T value ) {                                                  // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {                                                          // retrieve sorted value
        resume();
        return value;
    }
};

#endif