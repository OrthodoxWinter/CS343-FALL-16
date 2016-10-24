#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__ 1

_Task Multiplier {
	int **Z;
	int **X;
	int **Y;
	unsigned int xc;
	unsigned int yc;
	unsigned int minRow;
	unsigned int maxRow;

	void main();
	void computeRow(unsigned int rowToCompute);
	int multiplyXRowYColumn(int **X, int **Y, unsigned int xr, unsigned int yc, unsigned int dimension);

  public:
  	Multiplier(int **Z, int **X, int **Y, unsigned int xc, unsigned int yc, unsigned int minRow, unsigned maxRow);
};

#endif