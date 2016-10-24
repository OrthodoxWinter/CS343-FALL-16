#include "q2multiplier.h"

void Multiplier::main() {
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

void Multiplier::computeRow(unsigned int rowToCompute) {
	for (unsigned int i = 0; i < yc; i++) {
		Z[rowToCompute][i] = multiplyXRowYColumn(X, Y, rowToCompute, i, xc);
	}
}

int Multiplier::multiplyXRowYColumn(int **X, int **Y, unsigned int xr, unsigned int yc, unsigned int dimension) {
	int sum = 0;
	for (unsigned int i = 0; i < dimension; i++) {
		sum += X[xr][i] * Y[i][yc];
	}
	return sum;
}

Multiplier::Multiplier(int **Z, int **X, int **Y, unsigned int xc, unsigned int yc, unsigned int minRow, unsigned maxRow): Z(Z), X(X), Y(Y), xc(xc), yc(yc), minRow(minRow), maxRow(maxRow) {}