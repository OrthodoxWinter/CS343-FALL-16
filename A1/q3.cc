#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

_Coroutine FractionalConstant {
public:
	enum Status { CONT, MATCH };
private:
	char ch;
	Status status;
	
	void main() {
		status = CONT;																	// initialize status to CONT
		optSign();																		// optionally match a sign
		int wholeLength = digitSequence( 16, CONT );									// match at most 16 digits
		switch ( ch ) {																	// the first non-sign, none digit char indicates whether this is fractional
			case '.': { 																// a "." indicates this is a fractional constant
				if ( wholeLength > 0 ) status = MATCH;
				suspend();
	    		int decimalLength = digitSequence( 16 - wholeLength, MATCH );			// match digits after ".", if any.
				if ( wholeLength + decimalLength <= 0 ) _Throw Error();					// if no digits matched before and after ".", then throw error
		    	exponentPart();
		    	break;
		    }
		  	case 'e':
		  	case 'E':																	// if found "e" or "E", then it's non-fractional float constant
  				if ( wholeLength <= 0 ) _Throw Error();									// make sure matched at least 1 digit prior to the exponent
		    	exponentPart();
		    	break;
		  	default: 
		  		_Throw Error();
	 	} //switch
		if ( !( ch == 'f' || ch == 'l' || ch == 'F' || ch == 'L' ) ) _Throw Error();	// match float suffix. throw error if not valid suffix character
		suspend();
		_Throw Error();																	// can no longer match any more characters at this point, so throw Error
	}

	// Matches +, -, or nothing
	void optSign() {
		if ( ch == '+' || ch == '-' ) suspend();
	}

	/*
	 * Matches a sequence of digits at most length max.
	 *
	 * int max: maximum length of the sequence of digits to be matched
	 * Status onSuspend: the status the coroutine should have when 
	 * suspended while matching digit sequence.
	 *
	 * Returns the lenght of the digit sequence matched.
	 * This routine may return 0, in which case it failed to match 
	 * a digit sequence.
	 */
	int digitSequence( int max, Status onSuspend ) {
		int length;																		// the length of the digit sequence so far
		for ( length = 0; length < max; length += 1 ) {
			if ( !isdigit( ch ) ) return length;										// return on encoutnering non-digit
			status = onSuspend;
			suspend();
		} // for
		return length;
	}

	/* Matches the exponent part of a float constant or nothing.
	 * The exponent has up to 3 digits.
	 *
	 * Returns true if an exponent part was matched. Returns false otherwise
	 */
	bool exponentPart() {
		if ( ch == 'e' || ch == 'E' ) {
			status = CONT;
			suspend();
		} else {
			return false;																// Cannot match exponent if "e" or "E" not found.
		} // if
		optSign();
		if ( digitSequence( 3, MATCH ) <= 0 ) _Throw Error();							// Match at most 3 digits. If no digits are matched, then throw Error
		return true;
	}

public:
	_Event Error {};
	Status next( char c ) {
		ch = c;
		resume();
		return status;
	}
};


// print out the usage of this program and terminate
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    istream *infile = &cin;																// default input is cin

    switch ( argc ) {
    	case 2:																			// input file provided, therefore read from file
    		try {
    			infile = new ifstream(argv[1]);
    		} catch (uFile::Failure) {
    			cerr << "Error! Could not open input file \"" << argv[0] << "\"" << endl;
	    		usage( argv );
    		}
    		break;
    	case 1:
    		break;																		// no input file, use cin
		default:
			usage(argv);																// more than one argument, incorrect usage
    } // switch

    string str;
    for ( ;; ) {
	    FractionalConstant fc;
		if ( !getline( *infile, str ) ) break;											// get entire line from input
		cout << "\"" << str << "\" : ";
		if (str == "") {																// warning if line is blank
			cout << "Warning! Blank line." << endl;
			continue;
		} // if
		unsigned int i;
		cout << "\"";
		try {
			FractionalConstant::Status status = FractionalConstant::Status::CONT;
			for (i = 0; i < str.length(); i += 1) {										// loop each character of the line
				char c = str[i];
	      		cout << c;																// print out the character
	      		status = fc.next(c);													// call coroutine and get status
	      	}
	      	cout << "\" ";
	      	if (status == FractionalConstant::Status::MATCH) {
	      		cout << "yes" << endl;
	      	} else {
	      		cout << "no" << endl;
	      	} // if
	  	} catch (uBaseCoroutine::UnhandledException) {									// on exception, print "no" and output extraneous characters
	  		cout << "\" no";
	  		if (i < str.length() - 1) cout << " -- extraneous characters \"" << str.substr(i + 1, string::npos) <<"\"";
	  		cout << endl;
	  	} // try
    } // for
    if ( infile != &cin ) delete infile;												// close file if applicable
}