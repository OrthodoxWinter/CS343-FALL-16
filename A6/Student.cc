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

	; // Number of purchased soda
	for (unsigned int purchasedAmount = 0; purchasedAmount < numberToPurchase; purchasedAmount++){
		_Select(card || giftCard);
		yield(rng(9) + 1);
		bool bought = false;
		if (card.available()){
			while (!bought){
				try {
					vm->buy(favouriteFlavour, *(card()));
					bought = true;
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
			}
						
		} else {
			while (!bought){
				try {
					vm->buy(favouriteFlavour, *(card()));
					bought = true;
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
	}
	delete card();
	delete giftCard();
	prt.print(Printer::Kind::Student, id, 'F');
}


