#ifndef __POTATO_H__
#define __POTATO_H__ 1

 extern PRNG rng;

class Potato {
 	unsigned int ticks;

  public:
    _Event Explode {};
    Potato( unsigned int maxTicks = 10 );
    void reset( unsigned int maxTicks = 10 );
    void countdown();
};

#endif