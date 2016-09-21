#include <ctype.h>

using namespace std;

_Coroutine FractionalConstant {
public:
	enum Status { CONT, MATCH };
private:
	char ch = '';
	int mantissaLength = 0;
	int exponentLength = 0;
	Status status = CONT;
	
	void main() {
		optSign();
		bool noDigit = !mantissaDigits()
		switch ( ch ) {
			case '.': 	//fractional constant
				if ( !noDigit ) status = MATCH
				suspend();
	    		if ( !mantissaDigits( MATCH ) && noDigit ) throw Error();
		    	exponentPart();
		    	break;
		  	case 'e':
		  	case 'E':
		    	exponentPart();
		    	break;
		  	default: 
		  		throw Error();
	 	}
		if ( !( ch == 'f' || ch == 'l' || ch == 'F' || ch == 'L' ) ) throw Error();
	}

	void optSign() {
		if ( ch == '+' || ch == '-' ) suspend();
	}

	bool mantissaDigits( Status onSuspend = CONT ) {
		digitSequence(mantissaLength, 16, onSuspend);
	}

	bool digitSequence( int &length, int max, Status onSuspend ) {
		bool nonEmpty = false;
		for ( ;; ) {
			if ( !isdigit( ch ) ) break;
			if ( length >= max ) break;
			nonEmpty = true;
			length++;
			status = onSuspend;
			suspend();
		}
		return nonEmpty;
	}

	bool exponentPart() {
		status = CONT;
		if ( ch == 'e' || ch == 'E' ) {
			suspend();
		} else {
			return false;
		}
		optSign();
		if ( !digitSequence( exponentLength, 3, MATCH ) ) throw Error();
		return true;
	}

public:
	_Event Error {};
	Status next( char c ) {
		ch = c;
		resume();
		return status;
	}
}