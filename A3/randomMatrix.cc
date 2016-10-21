#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

int main( int argc, const char *argv[] ) {

	srand (time(NULL));

	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << (rand() % 20000 - 10000) << " ";
		}
		cout << endl;
	}
}