#include "q2multiplier.h"

void Multiplier::main() {
	if (minRow < maxRow) {													// view [minRow, maxRow] as the range of rows that the current task and its descendents compute. If minRow < maxRow, then spawn 2 child Multipliers
		unsigned int rowToCompute = (minRow + maxRow) / 2;					// row that the current task computes, which is the midpoint between minRow and maxRow
		int rightMin = rowToCompute + 1;									// attempt to spawn a left and right child, where left computes [minRow, rowToCompute - 1] and right computes [rowToCompute + 1, maxRow]
		int rightMax = maxRow;
		if (rightMin == 0) { 												// check and handle overflow
			rightMin = 1;
			rightMax = 0;
		}
		Multiplier left(Z, X, Y, xc, yc, minRow, rowToCompute - 1);			// left child. Note minRow and maxRow use a 1-based index, to prevent underflow
		Multiplier right(Z, X, Y, xc, yc, rightMin, rightMax);				// right child
		computeRow(rowToCompute - 1);
	} else {
		if (minRow == maxRow) {												// if minRow == maxRow, then we reached a leaf node, and no need to spawn more children
			computeRow(minRow - 1);
		}
	}
}

/*
 * compute the the specified row of Z using matrices X and Y
 */
void Multiplier::computeRow(unsigned int rowToCompute) {
	for (unsigned int i = 0; i < yc; i++) {
		Z[rowToCompute][i] = multiplyXRowYColumn(X, Y, rowToCompute, i, xc);
	}
}

/*
 * Multiplies the row xr of X by column yc of Y, which yields the value that corresponding to Z[xr][yc]
 */
int Multiplier::multiplyXRowYColumn(int **X, int **Y, unsigned int xr, unsigned int yc, unsigned int dimension) {
	int sum = 0;
	for (unsigned int i = 0; i < dimension; i++) {
		sum += X[xr][i] * Y[i][yc];
	}
	return sum;
}

Multiplier::Multiplier(int **Z, int **X, int **Y, unsigned int xc, unsigned int yc, unsigned int minRow, unsigned maxRow): Z(Z), X(X), Y(Y), xc(xc), yc(yc), minRow(minRow), maxRow(maxRow) {}