#include "Student.h"
#include "WATcardoffice.h"
#include "VendingMachine.h"
#include "printer.h"
#include "rng.h"
#include <iostream>
using namespace std;
 Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases){
 	numberToPurchase= (rng() % maxPurchases) + 1;
	int flavorIndex = (int) rng(NUM_FLAVORS - 1);
	favouriteFlavour = (VendingMachine::Flavours)flavorIndex;
	prt.print(Printer::Kind::Student, id, 'S', favouriteFlavour, numberToPurchase);

 };

void Student::main(){
	WATCard::FWATCard card = cardOffice.create(id, INITIAL_AMOUNT);
	WATCard::FWATCard giftCard = groupoff.giftCard();
	VendingMachine* vm = nameServer.getMachine(id);
	prt.print(Printer::Kind::Student, id, 'V', vm->getId());

	unsigned int purchasedAmount = 0; // Number of purchased soda
	WATCard *availableCard;
	WATCard *giftCardPtr = NULL;
	char state;
	yield(rng(9) + 1);
	bool isGiftcard = false;
	while (purchasedAmount < numberToPurchase) {
		_Select(card || giftCard);
		try {
			if (card.available()) {
				availableCard = card();
				isGiftcard = false;
				state = 'B';
			} else {
				giftCardPtr = giftCard();
				availableCard = giftCardPtr;
				isGiftcard = true;
				state = 'G';
			}
			vm->buy(favouriteFlavour, *availableCard);
			purchasedAmount++;
			prt.print(Printer::Kind::Student, id, state, availableCard->getBalance());
			if (isGiftcard) giftCard.reset();
			yield(rng(9) + 1);
		} catch(WATCardOffice::Lost) {// Attempt to rebuy if any exception thrown
			card = cardOffice.create(id, INITIAL_AMOUNT);
			prt.print(Printer::Kind::Student, id, 'L');
		} catch(VendingMachine::Funds) {
			//transfer if not enough money on card
			unsigned int transferAmount = vm->cost() + 5;
			card = cardOffice.transfer(id, transferAmount, availableCard);
		} catch(VendingMachine::Stock) {
			//get new vm if out of stock
			vm = nameServer.getMachine(id);
			prt.print(Printer::Kind::Student, id, 'V', vm->getId());
		}
	}
	//Do clean up
	try {
		delete card();
	} catch (WATCardOffice::Lost) {}
	if (giftCardPtr == NULL) {
		giftCardPtr = giftCard();
	}
	delete giftCardPtr;
	prt.print(Printer::Kind::Student, id, 'F');
}


