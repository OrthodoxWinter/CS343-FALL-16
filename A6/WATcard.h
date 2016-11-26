#ifndef __WATCARD_H__
#define __WATCARD_H__

class WATCard {
	unsigned int cardValue;
    WATCard( const WATCard & );               // prevent copying
    WATCard &operator=( const WATCard & );
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif