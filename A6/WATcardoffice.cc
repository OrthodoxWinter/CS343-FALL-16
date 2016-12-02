#include "WATcardoffice.h"
#include "rng.h"

WATCardOffice::WATCardOffice(Printer &printer, Bank &bank, unsigned int numCouriers) : printer(printer), bank(bank), numCouriers(numCouriers), terminate(false) {
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers[i] = new Courier(i, *this, bank, printer);
	}
}

WATCardOffice::~WATCardOffice() {
	for (unsigned int i = 0; i < numCouriers; i++) {
		delete couriers[i];
	}
	delete [] couriers;
}

WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice &office, Bank &bank, Printer &printer) : id(id), office(office), bank(bank), printer(printer) {}

void WATCardOffice::Courier::main() {
	printer.print(Printer::Kind::Courier, id, 'S');
	for (;;) {
		Job *job = office.requestWork();
		if (job == NULL) break;
		Args &args = job->args;
		if (rng(6) != 3) {
			printer.print(Printer::Kind::Courier, id, 't', args.sid, args.amount);
			bank.withdraw(args.sid, args.amount);
			args.card->deposit(args.amount);
			job->result.delivery(args.card);
			printer.print(Printer::Kind::Courier, id, 'T', args.sid, args.amount);
		} else {
			delete args.card;
			job->result.exception(new Lost());
		}
		delete job;
  	}
	printer.print(Printer::Kind::Courier, id, 'F');
}

void WATCardOffice::main() {
	printer.print(Printer::Kind::WATCardOffice, 'S');
	for (;;) {
		_Accept(~WATCardOffice) {
			terminate = true;
			for (unsigned int i = 0; i < numCouriers; i++) {
				_Accept(requestWork);
			}
			break;
		}
		or _Accept(create, transfer) {
			_Accept(requestWork);
		}
	}
	printer.print(Printer::Kind::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	WATCard *card = new WATCard();
	nextJob = new Job(Args(sid, card, amount));
	printer.print(Printer::Kind::WATCardOffice, 'C', sid, amount);
	return nextJob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	nextJob = new Job(Args(sid, card, amount));
	printer.print(Printer::Kind::WATCardOffice, 'T', sid, amount);
	return nextJob->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	if (terminate) return NULL;
	Job *job = nextJob;
	nextJob = NULL;
	return job;
}