#include "WATcard.h"

WATCard::WATCard() : cardValue(0) {}

void WATCard::deposit(unsigned int amount) {
	cardValue += amount;
}
void WATCard::withdraw( unsigned int amount ) {
	cardValue -= amount;
}
unsigned int WATCard::getBalance() {
	return cardValue;
}