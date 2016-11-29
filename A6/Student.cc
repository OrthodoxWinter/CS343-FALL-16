#include "Student.h"
#include <iostream>

 Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases){

 };

void Student::main(){
	try{
		for (;;){
			_Accept(~Student){
				break;
			}
			int numberToPurchase= rng(maxPurchases)+1;
			int favouriteFlavour = rng(3);
			WATCard::FWATCard card = cardOffice.create();
			WATCard::FWATCard gitCard = groupoff.giftCard();
			VendingMachine* vm = nameServer.getMachine();
			yield(rng(9) + 1);
			_Select(card, gitCard);

		}
		

	}catch(){

	}
}


~Student(){
	
}