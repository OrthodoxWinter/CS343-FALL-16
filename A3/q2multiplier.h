#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__ 1

/*
 * Each task Multiplier taks Matrix X and Y as input and computes a single row of Z = XY.
 * In addition, each task spawns at most 2 other Multiplier tasks to compute other rows of Z.
 */
_Task Multiplier {
	int **Z; 						// result matrix Z
	int **X; 						// input matrix X
	int **Y; 						// input matrix Y
	unsigned int xc; 				// number of columns X has
	unsigned int yc; 				// number of columns Y has
	unsigned int minRow;			// Since each task spawns (at most) 2 other tasks, these tasks can be seen as binary trees. [minRow, maxRow] represents the rows that this task and its descendent computes. 
	unsigned int maxRow;

	void main();
	void computeRow(unsigned int rowToCompute);
	int multiplyXRowYColumn(int **X, int **Y, unsigned int xr, unsigned int yc, unsigned int dimension);

  public:
  	Multiplier(int **Z, int **X, int **Y, unsigned int xc, unsigned int yc, unsigned int minRow, unsigned maxRow);
};

#endif