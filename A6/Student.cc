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
	prt.print(Printer::Kind::Student, id, 'S');

 };

void Student::main(){
	WATCard::FWATCard card = cardOffice.create(id, INITIAL_AMOUNT);
	WATCard::FWATCard giftCard = groupoff.giftCard();
	VendingMachine* vm = nameServer.getMachine(id);
	prt.print(Printer::Kind::Student, id, 'V', vm->getId());

	unsigned int purchasedAmount = 0; // Number of purchased soda
	while (purchasedAmount < numberToPurchase){
		_Select(card || giftCard);
		yield(rng(9) + 1);

		if (card.available()){
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				prt.print(Printer::Kind::Student, id, 'B', card()->getBalance());

			} catch(WATCardOffice::Lost){
				card = cardOffice.create(id, INITIAL_AMOUNT);
				prt.print(Printer::Kind::Student, id, 'L');
			} catch(VendingMachine::Funds){
				unsigned int transferAmount = vm->cost() + 5;
				card = cardOffice.transfer(id, transferAmount, card());
			} catch(VendingMachine::Stock){
				vm = nameServer.getMachine(id);
				prt.print(Printer::Kind::Student, id, 'V', vm->getId());
			}					
		} else {
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				prt.print(Printer::Kind::Student, id, 'G', giftCard()->getBalance());
				giftCard.reset();
			} catch(VendingMachine::Funds){
				unsigned int transferAmount = vm->cost() + 5;
				card = cardOffice.transfer(id, transferAmount, giftCard());
			} catch(VendingMachine::Stock){
				vm = nameServer.getMachine(id);
				prt.print(Printer::Kind::Student, id, 'V', vm->getId());
			}					

		}
	}
	delete giftCard();
	delete card();
	prt.print(Printer::Kind::Student, id, 'F');
}


