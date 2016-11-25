#include "WATcardoffice.h"
#include "rng.h"

void WATCardOffice::Courier::main() {
	while (;;) {
		Job *job = office.requestWork();
		if (job == NULL) break;
		WATCard *card = job->args.card;
		if (rng(5) != 0) {
			unsigned int amount = job->args.amount;
			bank.withdraw(job->args.id, amount);
			card->deposit(amount);
			job->result.deliver(card);
		} else {
			delete card;
			job->result.exception(new Lost());
		}
		delete job;
	}
}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers) : printer(printer), bank(bank), numCouriers(numCouriers), terminate(false) {}

void WATCardOffice::main() {
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers[i] = new Courier(bank, *this);
	}
	for (;;) {
		_Accept(~WATCardOffice) {
			terminate = true;
			for (unsigned int i = 0; i < numCouriers; i++) {
				_Accept(requestWork)
			}
			break;
		} _Or _Accept(create) {

		} _Or _Accept(transfer) {
			
		}
	}
}