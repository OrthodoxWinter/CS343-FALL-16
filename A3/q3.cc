#include <cstdlib>
#include <iostream>
#include "q3consumer.h"
#include "q3producer.h"
#include "q3buffer.h"

using namespace std;

void usage(char *argv[]) {
    cout << "Usage: " << argv[0]
     << " [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]" << endl;
    exit( EXIT_SUCCESS );
}

void uMain::main() {

    unsigned int cons = 5, prods = 3, produce = 10, bufferSize = 10, delays = 1;

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
    if (delays <= 0 || bufferSize <= 0 || produce <= 0 || prods <= 0 || cons <= 0) {
        usage(argv);
    }
    if (argc < 6) {
        delays = prods + cons;
    }

#ifdef __U_MULTI__
    uProcessor p[3] __attribute__ (( unused ));
#endif

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