#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h>				// getpid
#include <setjmp.h>
#include <cstring>

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

long int freq = 5;

jmp_buf buf;

long int Ackermann( long int m, long int n ) {
	jmp_buf tmp;
	if ( m == 0 ) {
		if ( random() % freq == 0 ) longjmp(buf, 1);
		return n + 1;
	} else if ( n == 0 ) {
		if ( random() % freq == 0 ) longjmp(buf, 1);
		memcpy(tmp, buf, sizeof tmp);
		if ( !setjmp(buf) ) {
			int rtn = Ackermann( m - 1, 1 );
			memcpy(buf, tmp, sizeof buf);
			return rtn;
		} else {
			print( cout << "E1 " << m << " " << n << endl );
			memcpy(buf, tmp, sizeof buf);
		}
	} else {
		memcpy(tmp, buf, sizeof tmp);
		if ( !setjmp(buf) ) {
			int rtn = Ackermann( m - 1, Ackermann( m, n - 1 ) );
			memcpy(buf, tmp, sizeof buf);
			return rtn;
		} else {
			print( cout << "E2 " << m << " " << n << endl );
			memcpy(buf, tmp, sizeof buf);
		}
	}
	return 0;	// recover by returning 0
}

int main( int argc, const char *argv[] ) {
	long int Ackermann( long int m, long int n );
	long int m = 4, n = 6, seed = getpid();	// default values

	switch ( argc ) {
	  case 5: freq = atoi( argv[4] );
	  case 4: seed = atoi( argv[3] );
	  case 3: n = atoi( argv[2] );
	  case 2: m = atoi( argv[1] );
	} // switch
	srandom( seed );
	cout << m << " " << n << " " << seed << " " << freq << endl;
	if ( !setjmp(buf) ) {
		cout << Ackermann( m, n ) << endl;
	} else {
		print( cout << "E3" << endl );
	}
}
