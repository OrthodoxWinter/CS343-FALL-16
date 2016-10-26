#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "q2multiplier.h"

using namespace std;

/*
 * Given a xr by xc matrix X and xc by yc matrix Y, multiple the 2 and store the result in Z
 */
void matrixmultiply(int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc) {
	Multiplier A(Z, X, Y, xc, yc, 1, xr);
}

/* 
 * print out the usage of this program and terminate
 */
void usage(char *argv[]) {
    cout << "Usage: " << argv[0]
	 << " xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]" << endl;
    exit( EXIT_SUCCESS );
}

/*
 * Allocate the columns of matrix X on the heap and set each entry in the matrix to 0
 * X is a mxn matrix, where m = rows, and n = columns
 */
void allocateMatrix(int *X[], unsigned int rows, unsigned int columns) {
	for (unsigned int i = 0; i < rows; i++) {
		X[i] = new int[columns];
        for (unsigned int j = 0; j < columns; j++) {
            X[i][j] = 0;
        }
	}
}

/*
 * Try to read matrix X from a given istream infile. If infile is NULL, then default all
 * all values of the matrix to 37. X is a mxn matrix, where m = rows, and n = columns
 */
void readMatrix(istream *infile, int *X[], unsigned int rows, unsigned int columns) {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			if (infile != NULL) {
                *infile >> X[i][j];
            } else {
                X[i][j] = 37;
            }
		}
	}
}

/*
 * Given an array which represent a row of a matrix, print it out with formatting
 */
void printMatrixRow(int *rowVector, unsigned int columns) {
	for (unsigned int i = 0; i < columns; i++) {
		cout.width(8);                                                                  // print elements with formatting
		cout << right << rowVector[i] << " ";
	}
}

/*
 * Given a matrix where the rows a allocated on the heap, free all the rows
 */
void freeMatrix(int *X[], unsigned int rows) {
	for (unsigned int i = 0; i < rows; i++) {
		delete[] X[i];
	}
}

void uMain::main() {

    istream *YInput = NULL;                                                             // initialize variables
    istream *XInput = NULL;

    unsigned int xr = 0;
    unsigned int yc = 0;
    unsigned int xcyr = 0;

    switch ( argc ) {
    	case 6:
    		try {
    			YInput = new ifstream(argv[5]);                                         // try to read y matrix file
    		} catch (uFile::Failure) {
    			cout << "Error! Could not open y-matrix input-file \"" << argv[5] << "\"" << endl;
	    		usage( argv );
    		}
            try {// try to read x matrix file
                XInput = new ifstream(argv[4]);
            } catch (uFile::Failure) {
                cout << "Error! Could not open x-matrix input-file \"" << argv[4] << "\"" << endl;
                usage( argv );
            }
    	case 4:
    		int m, n, k;                                                                // read the dimensions of matrices and terminate if less than 1
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

    uProcessor p[xr - 1] __attribute__ (( unused ));                                    // multiple processor for part b

    int *Z[xr];                                                                         // declare and allocate X, Y, and Z matrix
    int *X[xr];
    int *Y[xcyr];

    allocateMatrix(Z, xr, yc);
    allocateMatrix(X, xr, xcyr);
    allocateMatrix(Y, xcyr, yc);

    readMatrix(XInput, X, xr, xcyr);                                                    // read X and Y
    readMatrix(YInput, Y, xcyr, yc);

    delete YInput;												                        // close files
    delete XInput;

    matrixmultiply(Z, X, xr, xcyr, Y, yc);                                              // perform matrix multiplication

    if (argc == 6) {                                                                    // print output if input matrix specified
        for (unsigned int i = 0; i < xcyr; i++) {                                       // print the top half, where top left is empty, and top right is Y
            for (unsigned int j = 0; j < xcyr; j++) {                                   // top left
                cout.width(8);
                cout << "" << " ";
            }
            cout << "   | ";
            printMatrixRow(Y[i], yc);                                                   // top right
            cout << endl;
        }
        for (unsigned int i = 0; i < xcyr * 9 + 3; i++) {                               // print the middle separating row
            cout << "-";
        }
        cout << "*";
        for (unsigned int i = 0; i < yc * 9 + 1; i++) {
            cout << "-";
        }
        cout << endl;

        for (unsigned int i = 0; i < xr; i++) {                                         // print the bottom half, where bottom left is X, and bottom right is Z
            printMatrixRow(X[i], xcyr);                                                 // bottom left
            cout << "   | ";
            printMatrixRow(Z[i], yc);                                                   // bottom right
            cout << endl;
        }
    }

    freeMatrix(X, xr);                                                                  // free the matrices
    freeMatrix(Y, xcyr);
    freeMatrix(Z, xr);
}