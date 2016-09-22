#include <ctype.h>
#include <iostream>
#include <string>

using namespace std;

_Coroutine FractionalConstant {
public:
	enum Status { CONT, MATCH };
private:
	char ch;
	int mantissaLength;
	int exponentLength;
	Status status;
	
	void main() {
		mantissaLength = 0;
		exponentLength = 0;
		status = CONT;
		optSign();
		bool noDigit = !mantissaDigits();
		switch ( ch ) {
			case '.': 	//fractional constant
				if ( !noDigit ) status = MATCH;
				suspend();
	    		if ( !mantissaDigits( MATCH ) && noDigit ) throw Error(1);
		    	exponentPart();
    		 	status = MATCH;
		    	break;
		  	case 'e':
		  	case 'E':
		  		if (noDigit) throw Error(7);
		    	exponentPart();
		    	break;
		  	default: 
		  		throw Error(2);
	 	}
		if ( !( ch == 'f' || ch == 'l' || ch == 'F' || ch == 'L' ) ) throw Error(3);
		suspend();
		throw Error(6);
	}

	void optSign() {
		if ( ch == '+' || ch == '-' ) suspend();
	}

	bool mantissaDigits( Status onSuspend = CONT ) {
		return digitSequence(mantissaLength, 16, onSuspend);
	}

	bool digitSequence( int &length, int max, Status onSuspend ) {
		bool nonEmpty = false;
		for ( ;; ) {
			if ( !isdigit( ch ) ) break;
			if ( length >= max ) throw Error(4);
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
		if ( !digitSequence( exponentLength, 3, MATCH ) ) throw Error(5);
		return true;
	}

public:
	_Event Error {
	public:
		int type;
		Error(int type): type(type) {
			cout << " Exception type: " << type << " ";
		}
	};
	Status next( char c ) {
		ch = c;
		resume();
		return status;
	}
};

void uMain::main() {

    istream *infile = &cin;

    string str;
    for ( ;; ) {
	    FractionalConstant fc;
		if ( !getline(*infile, str) ) break;
		cout << "\"" << str << "\" : ";
		if (str == "") {
			cout << "Warning! Blank Line." << endl;
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
	  	} catch (...) {
	  		cout << "\" no";
	  		if (i < str.length() - 1) cout << " -- extraneous characters \"" << str.substr(i + 1, string::npos) <<"\"";
	  		cout << endl;
	  	}
    }
    if ( infile != &cin ) delete infile;
}