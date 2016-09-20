#include <iostream>
#include <unistd.h>
using namespace std;

class Fixup {
public:
    virtual void call() = 0;
};

void f( int &i, Fixup &fixup );

class RootFixup : public Fixup {
private:
    int &i;
public:
    RootFixup(int &i): i(i) {}
    void call() {
        cout << "root " << i << endl;
    }
};

class HandlerFixup : public Fixup {
private:
    Fixup *prev;
    int &i;
public:
    HandlerFixup(Fixup *prev, int &i): prev(prev), i(i) {}
    void call() {
        cout << "f handler " << i << endl;
        i -= 1;
        f( i, *prev );
    }
};

void f( int &i, Fixup &fixup ) {
    cout << "f " << i << endl;
    if ( rand() % 5 == 0 ) fixup.call();              // require correction ?
    i -= 1;
    HandlerFixup newFixup = HandlerFixup( &fixup, i );
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
    RootFixup fixup = RootFixup(times);
    f( times, fixup );
}