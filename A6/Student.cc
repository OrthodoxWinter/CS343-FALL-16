#include "Student.h"
#include "WATcardoffice.h"
#include "VendingMachine.h"
#include "printer.h"
#include "rng.h"
#include <iostream>
using namespace std;
 Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases){
 	numberToPurchase= rng(maxPurchases)+1;
	int flavorIndex = (int) rng(NUM_FLAVORS);
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
	while (purchasedAmount < numberToPurchase) {
		_Select(card || giftCard);
		try {
			if (card.available()) {
				availableCard = card();
				state = 'B';
			} else {
				giftCardPtr = giftCard();
				availableCard = giftCardPtr;
				giftCard.reset();
				state = 'G';
			}
			yield(rng(9) + 1);
			vm->buy(favouriteFlavour, *availableCard);
			purchasedAmount++;
			prt.print(Printer::Kind::Student, id, state, availableCard->getBalance());
		} catch(WATCardOffice::Lost) {
			card = cardOffice.create(id, INITIAL_AMOUNT);
			prt.print(Printer::Kind::Student, id, 'L');
		} catch(VendingMachine::Funds) {
			unsigned int transferAmount = vm->cost() + 5;
			card = cardOffice.transfer(id, transferAmount, availableCard);
		} catch(VendingMachine::Stock) {
			vm = nameServer.getMachine(id);
			prt.print(Printer::Kind::Student, id, 'V', vm->getId());
		}
	}
	try {
		delete card();
	} catch (WATCardOffice::Lost) {}
	if (giftCardPtr == NULL) {
		giftCardPtr = giftCard();
	}
	delete giftCardPtr;
	prt.print(Printer::Kind::Student, id, 'F');
}


