#include <cstdlib>                    // atoi
#include <iostream>
using namespace std;

// volatile prevents dead-code removal
void do_work( int C1, int C2, int C3, int L1, int L2, volatile int L3 ) {
    bool doL1, doL2, doL3;
    int i, j, k;
    bool s7, s8;
    doL1 = true;
    if (L1 == 0) doL1 = false;
    i = 0;
    s8 = true;
    while ( doL1 ) {
#ifndef NOOUTPUT
        cout << "S1 i:" << i << endl;
#endif
        doL2 = true;
        if (L2 == 0) doL2 = false;
        j = 0;
        s7 = true;
        while ( doL2 ) {
#ifndef NOOUTPUT
            cout << "S2 i:" << i << " j:" << j << endl;
#endif
            doL3 = true;
            if (L3 == 0) doL3 = false;
            k = 0;
            while ( doL3 ) {
#ifndef NOOUTPUT
                cout << "S3 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                if ( C1 ) {
                    doL3 = false;
                    doL2 = false;
                    doL1 = false;
                    s7 = false;
                    s8 = false; 
                } else {
#ifndef NOOUTPUT
                    cout << "S4 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                    if ( C2 ) {
                        doL2 = false;
                        doL3 = false;
                        s7 = false;
                    } else {
#ifndef NOOUTPUT
                        cout << "S5 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                        if ( C3 ) {
                            doL3 = false;
                        } else {
#ifndef NOOUTPUT
                            cout << "S6 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                        }
                    }
                }
                k++;
                if (k == L3) doL3 = false;
            } // for
#ifndef NOOUTPUT
            if (s7) cout << "S7 i:" << i << " j:" << j << endl;
#endif
            j++;
            if (j == L2) doL2 = false;
        } // for
#ifndef NOOUTPUT
        if (s8) cout << "S8 i:" << i << endl;
#endif
        i++;
        if (i == L1) doL1 = false;
    } // for
    if (s7 && s8) s7 = s7 && s8;
} // do_work

int main( int argc, char *argv[] ) {
    int times = 1, L1 = 10, L2 = 10, L3 = 10;
    switch ( argc ) {
      case 5:
        L3 = atoi( argv[4] );
        L2 = atoi( argv[3] );
        L1 = atoi( argv[2] );
        times = atoi( argv[1] );
        break;
      default:
        cerr << "Usage: " << argv[0] << " times L1 L2 L3" << endl;
        exit( EXIT_FAILURE );
    } // switch

    for ( int i = 0; i < times; i += 1 ) {
        for ( int C1 = 0; C1 < 2; C1 += 1 ) {
            for ( int C2 = 0; C2 < 2; C2 += 1 ) {
                for ( int C3 = 0; C3 < 2; C3 += 1 ) {
                    do_work( C1, C2, C3, L1, L2, L3 );
#ifndef NOOUTPUT
                    cout << endl;
#endif
                } // for
            } // for
        } // for
    } // for
} // main
