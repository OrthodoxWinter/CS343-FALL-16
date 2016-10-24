#include <cstdlib>
#include <iostream>
#include "q3consumer.h"
#include "q3producer.h"
#include "q3buffer.h"

using namespace std;

void usage(char *argv[]) {
    cerr << "Usage: " << argv[0]
     << " [infile-file]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main() {

    unsigned int cons = 5, prods = 3, produce = 10, bufferSize = 10, delays = 0;

    switch ( argc ) {
    	case 6:																			// input file provided, therefore read from file
    		delays = atoi(argv[5]);
        case 5:
            bufferSize = atoi(argv[4]);
    	case 4:
            produce = atoi(argv[3]);
        case 3:
            prods = atoi(argv[2]);
        case 2: 
            cons = atoi(argv[1]);
    		break;																		// no input file, use cin
		case 1:
            break;
        default:
			usage(argv);																// more than one argument, incorrect usage
    } // switch
    if (argc < 6) {
        delays = prods + cons;
    }

    BoundedBuffer<int> buffer(bufferSize);
    Producer *producers[prods];
    Consumer *consumers[cons];
    int sums[cons];
    for (unsigned int i = 0; i < prods; i++) {
        producers[i] = new Producer(buffer, produce, delays);
    }
    for (unsigned int i = 0; i < cons; i++) {
        sums[i] = 0;
        consumers[i] = new Consumer(buffer, delays, SENTINEL, sums[i]);
    }

    for (unsigned int i = 0; i < prods; i++) {
        delete producers[i];
    }

    for (unsigned int i = 0; i < cons; i++) {
        buffer.insert(SENTINEL);
    }

    for (unsigned int i = 0; i < cons; i++) {
        delete consumers[i];
    }

    int sum = 0;
    for (unsigned int i = 0; i < cons; i++) {
        sum += sums[i];
    }
    cout << "total: " << sum << endl;
}