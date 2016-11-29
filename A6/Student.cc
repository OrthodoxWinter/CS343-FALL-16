#include "Student.h"
#include <iostream>

 Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases){
 	numberToPurchase= rng(maxPurchases)+1;
	favouriteFlavour = rng(3);
	printer.print(Printer::Kind::Student, 'S', id);

 };

void Student::main(){
	WATCard::FWATCard card = cardOffice.create();
	WATCard::FWATCard giftCard = groupoff.giftCard();
	VendingMachine* vm = nameServer.getMachine();
	printer.print(Printer::Kind::Student, 'V', vm->getId());

	unsigned int purchasedAmount = 0; // Number of purchased soda
	for (; purchasedAmount < numberToPurchase;){
		_Select(card || gitCard);
		yield(rng(9) + 1);

		if (card.available()){
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				printer.print(Printer::Kind::Student, 'B', card->getBalance());

			} catch(_Event Lost){
				card = office.create(id, INITIAL_AMOUNT);
				printer.print(Printer::Kind::Student, 'L');
			} catch(_Event Funds){
				unsigned int transferAmount = vm.cost() + 5;
				WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
				card = cardOffice.transfer(id, transferAmount, card());
			} catch(_Event Stock){
				vm = nameServer.getMachine();
				printer.print(Printer::Kind::Student, 'V', vm->getId());
			}					
		} else {
			try {
				vm->buy(favouriteFlavour, *(card()));
				purchasedAmount += 1;
				printer.print(Printer::Kind::Student, 'G', giftCard->getBalance());
			} catch(_Event Funds){
				unsigned int transferAmount = vm.cost() + 5;
				WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *giftCard );
				card = cardOffice.transfer(id, transferAmount, giftCard());
			} catch(_Event Stock){
				vm = nameServer.getMachine();
				printer.print(Printer::Kind::Student, 'V', vm->getId());
			}					

		}
		

	}
	printer.print(Printer::Kind::Student, 'F');


}


~Student Student::(){

}