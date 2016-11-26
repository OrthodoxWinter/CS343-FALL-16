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

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers) : printer(printer), bank(bank), numCouriers(numCouriers), terminate(false), jobs(numCouriers) {}

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
		} 
		or _Accept(create || transfer)
		or _When(jobs.size() > 0) _Accept(requestWork)
	}
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	WATCard *card = new WATCard();
	Args args(id, amount, card);
	Job *job = new Job(args)
	jobs.push(job);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Args args(id, amount, card);
	Job *job = new Job(args)
	jobs.push(job);
	return job->result;
}

WATCardOffice::~WATCardOffice() {
	//not going to check if job queue is non-empty, because if the program executes correctly, it should be empty at this point
	for (unsigned int i = 0; i < numCouriers; i++) {
		delete couriers[i];
	}
	delete[] couriers;
}

Job *WATCardOffice::requestWork() {
	Job* job = jobs.front();
	jobs.pop();
	return job;
}