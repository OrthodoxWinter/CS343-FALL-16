#include <iostream>
#include <fstream>

using namespace std;

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;            // value denoting end of set
    T value;                     // communication: value being passed down/up the tree
    Binsertsort<T> *left;
    Binsertsort<T> *right;
    T nodeValue;
    void main() {
        cout << "in " << value << endl;
        left = NULL;
        right = NULL;
        nodeValue = value;
        if (nodeValue != Sentinel) suspend();
        for (;;) {
            if (value == Sentinel) { 
                cout << "sentinel value";
                break;
            }
            Binsertsort<T> **child;
            if (value < nodeValue) {
                child = &left;
            } else {
                child = &right;
            }
            cout << "child is " << child << endl;
            if ((*child) == NULL) {
                (*child) = new Binsertsort<T>(Sentinel);
            }
            (*child)->sort(value);
            suspend();
        }
        suspend();

        //note that this coroutine is written such that if nodeValue is Sentinel, then left and right will always be NULL

        if (left != NULL) {
            left->sort(Sentinel);
            for (;;) {
                value = left->retrieve();
                if (value != Sentinel) {
                    suspend();
                } else {
                    break;
                }
            }
        }
        value = nodeValue;
        if (nodeValue != Sentinel) suspend();

        if (right != NULL) {
            right->sort(Sentinel);
            for (;;) {
                value = right->retrieve();
                if (value != Sentinel) {
                    suspend();
                } else {
                    break;
                }
            }
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
    ~Binsertsort() {
        delete left;
        delete right;
    }
};

// print out the usage of this program and terminate
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
     << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    istream *infile = &cin;                                                             // default input is cin

    switch ( argc ) {
        case 2:                                                                         // input file provided, therefore read from file
            try {
                infile = new ifstream(argv[1]);
            } catch (uFile::Failure) {
                cerr << "Error! Could not open input file \"" << argv[0] << "\"" << endl;
                usage( argv );
            }
            break;
        case 1:
            break;                                                                      // no input file, use cin
        default:
            usage(argv);                                                                // more than one argument, incorrect usage
    } // switch

    Binsertsort<int> sort(-1);
    int value;
    while(cin >> value) {
        if (value == -1) break;
        sort.sort(value);
    }

    sort.sort(-1);

    for (;;) {
        cout << "retrieve" << endl;
        int sortedValue = sort.retrieve();
        if (sortedValue == -1) {
            cout << "end";
            break;
        }
        cout <<"!!!" << sortedValue << " ";
    }

    if ( infile != &cin ) delete infile;                                                // close file if applicable
}
