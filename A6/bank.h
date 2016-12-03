#ifndef __BANK_H__
#define __BANK_H__

_Monitor Bank {
	unsigned int *bankAmount;// Student account balance
	unsigned int *toWithdraw; // comunicate variable
	uCondition *bench;
  public:
    Bank( unsigned int numStudents ); // constructor for bank, manages student account information
    void deposit( unsigned int id, unsigned int amount ); // store money for bank
    void withdraw( unsigned int id, unsigned int amount );// withdraw money from bank
    ~Bank();
};

#endif