#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "q1binsertsort.h"

using namespace std;

/*
 * This is an example type that can be sorted using Binsertsort.
 * It provides a == operator and < operator, as specified in the assignment
 */
class TwoNumbers {
  public:
    int value1;
    int value2;
    TwoNumbers(int value1, int value2): value1(value1), value2(value2) {}
    TwoNumbers() {}
    bool operator<(const TwoNumbers &c) {
        if (value1 == c.value1) {
            return value2 < c.value2;
        } else {
            return value1 < c.value1;
        }
    }

    bool operator==(const TwoNumbers &c) {
        return (value1 == c.value1) && (value2 == c.value2);
    }
};

/*
 * This function is an example usage of using BinsertSort to sort 
 * the type TwoNumbers defined above
 */
void sortTwoNumbers() {
    TwoNumbers sentinel(-1, -1);                                                        // Sentinel Value
    Binsertsort<TwoNumbers> sort(sentinel);
    TwoNumbers one(1, 6);                                                               // Values to sort
    TwoNumbers two(7, 5);
    TwoNumbers three(6, 3);
    TwoNumbers four(6, 6);
    sort.sort(one);
    sort.sort(two);
    sort.sort(three);
    sort.sort(four);
    sort.sort(sentinel);
    for (int i = 0; i < 4; i++) {                                                       // retrieve and print out the sorted values
        TwoNumbers value = sort.retrieve();
        cout << value.value1 << " " << value.value2 << endl;
    }
}

// print out the usage of this program and terminate
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
     << " unsorted-file [ sorted-file ]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    istream *infile;
    ostream *outfile = &cout;                                                           // default output is cout

    switch ( argc ) {
        case 3:                                                                         // output file specified, therefore open stream to write to file
            try {
                outfile = new ofstream(argv[2]);
            } catch (uFile::Failure) {
                cout << "Error! Could not open output file \"" << argv[2] << "\"" << endl;
                usage(argv);
            } // try
        case 2:                                                                         // open stream to read from input file
            try {
                infile = new ifstream(argv[1]);
            } catch (uFile::Failure) {
                cout << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                usage(argv);
            } // try
            break;
        default:
            usage(argv);                                                                // too many or too few arguments, show correct usage
    } // switch

    string line;

    while (getline(*infile, line)) {                                                    // read input file one line at a time
        if (line == "") {
            continue;                                                                   // move on to next line if encountered an empty line
        }
        stringstream input(line);

        Binsertsort<int> sort(SENTINEL);
        int numValue;                                                                   // number of values to sort on current line
        int value;

        input >> numValue;
        for (int i = 0; i < numValue; i++) {                                            // read the numbers and sort them
            input >> value;
            *outfile << value << " ";
            sort.sort(value);
        }

        *outfile << endl;

        sort.sort(SENTINEL);                                                            // send SENTINEL to indicate end of input

        for (int i = 0; i < numValue; i++) {                                            // retrieve and print the sorted values
            int sortedValue = sort.retrieve();
            *outfile << sortedValue << " ";
        }
        *outfile << endl << endl;
    }

    delete infile;                                                                      // release resources
    if (outfile != &cout) delete outfile;
}
