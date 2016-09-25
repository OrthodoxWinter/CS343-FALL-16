#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h>				// getpid
#include <setjmp.h>
#include <cstring>
#include <functional>

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

long int freq = 5;

jmp_buf buf;

int tryCatch( function< int() > &tryBlock, function< void() > &catchBlock ) {
	jmp_buf tmp;
	memcpy( tmp, buf, sizeof tmp );
	if ( !setjmp( buf ) ) {
		int rtn = tryBlock();
		memcpy( buf, tmp, sizeof buf );
		return rtn;
	} else {
		catchBlock();
		memcpy( buf, tmp, sizeof buf );
		return 0;
	}
}

long int Ackermann( long int m, long int n ) {
	if ( m == 0 ) {
		if ( random() % freq == 0 ) longjmp( buf, 1 );
		return n + 1;
	} else if ( n == 0 ) {
		if ( random() % freq == 0 ) longjmp( buf, 1 );
		function< int() > tryBlock = [m] () { return Ackermann( m - 1, 1 ); };
		function< void() > catchBlock = [ m, n ] () { print( cout << "E1 " << m << " " << n << endl ); };
		return tryCatch( tryBlock, catchBlock );
	} else {
		function < int() > tryBlock = [m, n] () { return Ackermann( m - 1, Ackermann( m, n - 1 ) ); };
		function < void() > catchBlock = [ m, n ] () { print( cout << "E2 " << m << " " << n << endl ); };
		return tryCatch( tryBlock, catchBlock );
	}
}

int main( int argc, const char *argv[] ) {
	long int Ackermann( long int m, long int n );
	long int m = 4, n = 6, seed = getpid();

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
