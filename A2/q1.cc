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
        suspend();
        if (nodeValue != Sentinel) {
            Binsertsort<T> leftChild(Sentinel);
            Binsertsort<T> rightChild(Sentinel);
            left = &leftChild;
            right = &rightChild;
            for (;;) {
                if (value == Sentinel) { 
                    cout << "sentinel value" << endl;
                    break;
                }
                Binsertsort<T> *child = value < nodeValue? left : right;
                cout << "child is " << child << endl;
                child->sort(value);
                suspend();
            }

            left->sort(Sentinel);
            right->sort(Sentinel);

            suspend();

            for (;;) {
                value = left->retrieve();
                if (value != Sentinel) {
                    suspend();
                } else {
                    break;
                }
            }

            value = nodeValue;
            suspend();

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
        cout <<"!!!" << sortedValue << " ";
        if (sortedValue == -1) {
            cout << "end";
            break;
        }
    }

    if ( infile != &cin ) delete infile;                                                // close file if applicable
}
