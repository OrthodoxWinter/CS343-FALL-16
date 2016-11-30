#include "Student.h"
#include "WATcardoffice.h"
#include "VendingMachine.h"
#include "printer.h"
#include "rng.h"
#include <iostream>

 Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases){
 	numberToPurchase= rng(maxPurchases)+1;
	int flavorIndex = (int) rng(NUM_FLAVORS);
	favouriteFlavour = (VendingMachine::Flavours)flavorIndex;
	prt.print(Printer::Kind::Student, 'S', id);

 };

void Student::main(){
	WATCard::FWATCard card = cardOffice.create(id, INITIAL_AMOUNT);
	WATCard::FWATCard giftCard = groupoff.giftCard();
	VendingMachine* vm = nameServer.getMachine(id);
	prt.print(Printer::Kind::Student, 'V', vm->getId());

	unsigned int purchasedAmount = 0; // Number of purchased soda
	for (; purchasedAmount < numberToPurchase;){
		_Select(card || giftCard);
		yield(rng(9) + 1);

		if (card.available()){
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				prt.print(Printer::Kind::Student, 'B', card()->getBalance());

			} catch(_Event WATCardOffice::Lost){
				card = cardOffice.create(id, INITIAL_AMOUNT);
				prt.print(Printer::Kind::Student, 'L');
			} catch(_Event VendingMachine::Funds){
				unsigned int transferAmount = vm->cost() + 5;
				card = cardOffice.transfer(id, transferAmount, card());
			} catch(_Event VendingMachine::Stock){
				vm = nameServer.getMachine(id);
				prt.print(Printer::Kind::Student, 'V', vm->getId());
			}					
		} else {
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				prt.print(Printer::Kind::Student, 'G', giftCard()->getBalance());
				giftCard.reset();
			} catch(_Event VendingMachine::Funds){
				unsigned int transferAmount = vm->cost() + 5;
				card = cardOffice.transfer(id, transferAmount, giftCard());
			} catch(_Event VendingMachine::Stock){
				vm = nameServer.getMachine(id);
				prt.print(Printer::Kind::Student, 'V', vm->getId());
			}					

		}
		

	}
	delete giftCard();
	delete card();
	prt.print(Printer::Kind::Student, 'F');


}


