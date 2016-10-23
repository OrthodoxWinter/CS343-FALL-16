#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

_Task Multiplier {
	int **Z;
	int **X;
	int **Y;
	unsigned int xc;
	unsigned int yc;
	unsigned int minRow;
	unsigned int maxRow;

	void main() {
		if (minRow < maxRow) {
			unsigned int rowToCompute = (minRow + maxRow) / 2;
			int rightMin = rowToCompute + 1;
			int rightMax = maxRow;
			if (rightMin == 0) {
				rightMin = 1;
				rightMax = 0;
			}
			Multiplier A(Z, X, Y, xc, yc, minRow, rowToCompute - 1);
			Multiplier B(Z, X, Y, xc, yc, rightMin, rightMax);
			computeRow(rowToCompute - 1);
		} else {
			if (minRow == maxRow) {
				computeRow(minRow - 1);
			}
		}
	}

	void computeRow(unsigned int rowToCompute) {
		for (int i = 0; i < yc; i++) {
			Z[rowToCompute][i] = multiplyXRowYColumn(X, Y, rowToCompute, i, xc);
		}
	}

	int multiplyXRowYColumn(int **X, int **Y, unsigned int xr, unsigned int yc, unsigned int dimension) {
		int sum = 0;
		for (int i = 0; i < dimension; i++) {
			sum += X[xr][i] * Y[i][yc];
		}
		return sum;
	}

  public:

  	Multiplier(int **Z, int **X, int **Y, unsigned int xc, unsigned int yc, unsigned int minRow, unsigned maxRow): Z(Z), X(X), Y(Y), xc(xc), yc(yc), minRow(minRow), maxRow(maxRow) {}
};

void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc ) {
	Multiplier A(Z, X, Y, xc, yc, 1, xr);
}

// print out the usage of this program and terminate
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void allocateMatrix(int *X[], unsigned int rows, unsigned int columns) {
	for (int i = 0; i < rows; i++) {
		X[i] = new int[columns];
	}
}

void readMatrix(istream *infile, int *X[], unsigned int rows, unsigned int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			*infile >> X[i][j];
		}
	}
}

void printMatrixRow(int *rowVector, unsigned int columns) {
	for (int i = 0; i < columns; i++) {
		cout.width(8);
		cout << right << rowVector[i] << " ";
	}
}

void freeMatrix(int *X[], unsigned int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] X[i];
	}
}

void uMain::main() {

    istream *YInput = &cin;																// default input is cin
    istream *XInput = &cin;

    unsigned int xr = 0;
    unsigned int yc = 0;
    unsigned int xcyr = 0;

    switch ( argc ) {
    	case 6:																			// input file provided, therefore read from file
    		try {
    			YInput = new ifstream(argv[5]);
    			XInput = new ifstream(argv[4]);
    		} catch (uFile::Failure) {
    			cout << "Error! Could not open input file \"" << argv[5] << "\"" << endl;
	    		usage( argv );
    		}
    	case 4:
    		int m, n, k;
    		m = atoi(argv[1]);
    		n = atoi(argv[2]);
    		k = atoi(argv[3]);
    		if (m < 1 || n < 1 || k < 1) {
    			usage(argv);
    		}
    		xr = m;
    		xcyr = n;
    		yc = k;
    		break;																		// no input file, use cin
		default:
			usage(argv);																// more than one argument, incorrect usage
    } // switch

    int *Z[xr];
    int *X[xr];
    int *Y[xcyr];

    allocateMatrix(Z, xr, yc);
    allocateMatrix(X, xr, xcyr);
    allocateMatrix(Y, xcyr, yc);

    readMatrix(XInput, X, xr, xcyr);
    readMatrix(YInput, Y, xcyr, yc);

    if ( YInput != &cin ) delete YInput;												// close file if applicable
    if ( XInput != &cin ) delete XInput;

    matrixmultiply(Z, X, xr, xcyr, Y, yc);

    for (int i = 0; i < xcyr; i++) {
    	for (int j = 0; j < xcyr; j++) {
    		cout.width(8);
    		cout << "" << " ";
    	}
    	cout << "   | ";
    	printMatrixRow(Y[i], yc);
    	cout << endl;
    }
    for (int i = 0; i < xcyr * 9 + 3; i++) {
    	cout << "-";
    }
    cout << "*";
    for (int i = 0; i < yc * 9 + 1; i++) {
    	cout << "-";
    }
    cout << endl;

    for (int i = 0; i < xr; i++) {
    	printMatrixRow(X[i], xcyr);
    	cout << "   | ";
    	printMatrixRow(Z[i], yc);
    	cout << endl;
    }

    freeMatrix(X, xr);
    freeMatrix(Y, xcyr);
    freeMatrix(Z, xr);
}