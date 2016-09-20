#include <iostream>
#include <unistd.h>
using namespace std;

class Fixup;

void f( int &i, Fixup &fixup );

class Fixup {
    private:
        Fixup *prev;
    
    public:
        int fixupType;
        int &i;
        Fixup( int fixupType, int &i, Fixup *prev): prev(prev), fixupType(fixupType), i(i) {}
        void call() {
            if ( fixupType ) {
                cout << "f handler " << i << endl;
                i -= 1;
                f( i, *prev );
            } else {
                cout << "root " << i << endl;
            }
        }
};
void f( int &i, Fixup &fixup ) {
    cout << "f " << i << endl;
    if ( rand() % 5 == 0 ) fixup.call();              // require correction ?
    i -= 1;
    Fixup newFixup = Fixup( 1, i, &fixup );
    if ( 0 < i ) f( i, newFixup );
}
int main( int argc, const char *argv[] ) {
    int times = 25, seed = getpid();
    switch ( argc ) {
      case 3: seed = atoi( argv[2] );                   // allow repeatable experiment
      case 2: times = atoi( argv[1] );                  // control recursion depth
      case 1: break;                                    // defaults
      default: cerr << "Usage: " << argv[0] << " times seed" << endl; exit( EXIT_FAILURE );
    }
    srand( seed );                                      // fixed or random seed
    Fixup fixup = Fixup( 0, times, NULL );
    f( times, fixup );
}