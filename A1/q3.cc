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
		status = CONT;
		optSign();
		int length1 = digitSequence(16, CONT);
		switch ( ch ) {
			case '.': { 	//fractional constant
				if ( length1 > 0 ) status = MATCH;
				suspend();
	    		int length2 = digitSequence(16 - length1, MATCH);
				if (length1 + length2 <= 0)  Error();
		    	exponentPart();
		    	break;
		    }
		  	case 'e':
		  	case 'E':
  				if (length1 <= 0) _Throw Error();
		    	exponentPart();
		    	break;
		  	default: 
		  		_Throw Error();
	 	}
		if ( !( ch == 'f' || ch == 'l' || ch == 'F' || ch == 'L' ) ) _Throw Error();
		suspend();
		_Throw Error();
	}

	void optSign() {
		if ( ch == '+' || ch == '-' ) suspend();
	}

	int digitSequence( int max, Status onSuspend ) {
		int length;
		for (length = 0; length < max; length++) {
			if ( !isdigit( ch ) ) return length;
			status = onSuspend;
			suspend();
		}
		return length;
	}

	bool exponentPart() {
		if ( ch == 'e' || ch == 'E' ) {
			status = CONT;
			suspend();
		} else {
			return false;
		}
		optSign();
		if ( digitSequence( 3, MATCH ) <= 0 ) _Throw Error();
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


void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    istream *infile = &cin;

    switch (argc) {
    	case 2: 
    		try {
    			infile = new ifstream(argv[1]);
    		} catch (uFile::Failure) {
    			cerr << "Error! Could not open input file \"" << argv[0] << "\"" << endl;
	    		usage( argv );
    		}
    		break;
    	case 1:
    		break;
		default:
			usage(argv);
    }

    string str;
    for ( ;; ) {
	    FractionalConstant fc;
		if ( !getline(*infile, str) ) break;
		cout << "\"" << str << "\" : ";
		if (str == "") {
			cout << "Warning! Blank line." << endl;
			continue;
		}
		unsigned int i;
		cout << "\"";
		try {
			FractionalConstant::Status status;
			for (i = 0; i < str.length(); i++) {
				char c = str[i];
	      		cout << c;
	      		status = fc.next(c);
	      	}
	      	cout << "\" ";
	      	if (status == FractionalConstant::Status::MATCH) {
	      		cout << "yes" << endl;
	      	} else {
	      		cout << "no" << endl;
	      	}
	  	} catch (uBaseCoroutine::UnhandledException) {
	  		cout << "\" no";
	  		if (i < str.length() - 1) cout << " -- extraneous characters \"" << str.substr(i + 1, string::npos) <<"\"";
	  		cout << endl;
	  	}
    }
    if ( infile != &cin ) delete infile;
}