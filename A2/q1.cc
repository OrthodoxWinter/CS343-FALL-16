#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "q1binsertsort.h"

using namespace std;

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

// print out the usage of this program and terminate
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
     << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    istream *infile;                                                                    // default input is cin
    ostream *outfile = &cout;

    switch ( argc ) {
        case 3:                                                                         // input file provided, therefore read from file
            try {
                outfile = new ofstream(argv[2]);
            } catch (uFile::Failure) {
                cout << "Error! Could not create output file \"" << argv[2] << "\"" << endl;
            }
        case 2:
            try {
                infile = new ifstream(argv[1]);
            } catch (uFile::Failure) {
                cout << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
            }
            break;                                                                      // no input file, use cin
        default:
            usage(argv);                                                                // more than one argument, incorrect usage
    } // switch

    string line;

    while (getline(*infile, line)) {
        if (line == "") {
            continue;
        }
        stringstream input(line);

        Binsertsort<int> sort(SENTINEL);
        int numValue;
        int value;

        input >> numValue;
        for (int i = 0; i < numValue; i++) {
            input >> value;
            *outfile << value << " ";
            sort.sort(value);
        }
        *outfile << endl;

        sort.sort(SENTINEL);

        for (int i = 0; i < numValue; i++) {
            int sortedValue = sort.retrieve();
            *outfile << sortedValue << " ";
        }
        *outfile << endl << endl;
    }

    delete infile;
    if (outfile != &cout) delete outfile;
}
