#include "WATcardoffice.h"
#include "rng.h"

WATCardOffice::WATCardOffice(Printer &printer, Bank &bank, unsigned int numCouriers) : printer(printer), bank(bank), numCouriers(numCouriers), terminate(false) {
	//initialize the couriers
	couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers[i] = new Courier(i, *this, bank, printer);
	}
}

WATCardOffice::~WATCardOffice() {
	//delete all the couriers
	for (unsigned int i = 0; i < numCouriers; i++) {
		delete couriers[i];
	}
	delete [] couriers;
}

WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice &office, Bank &bank, Printer &printer) : id(id), office(office), bank(bank), printer(printer) {}

void WATCardOffice::Courier::main() {
	printer.print(Printer::Kind::Courier, id, 'S');
	for (;;) {
		//get job
		Job *job = office.requestWork();
		//if job==NULL implies need to end
		if (job == NULL) break;
		Args &args = job->args;
		if (rng(6) != 3) {
			//card is not lost
			printer.print(Printer::Kind::Courier, id, 't', args.sid, args.amount);
			//withdraw amount and deposit
			bank.withdraw(args.sid, args.amount);
			args.card->deposit(args.amount);
			job->result.delivery(args.card);
			printer.print(Printer::Kind::Courier, id, 'T', args.sid, args.amount);
		} else {
			//card is lost
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
			//destructor called. Set flag and wait for couriers to receive message
			terminate = true;
			for (unsigned int i = 0; i < numCouriers; i++) {
				_Accept(requestWork);
			}
			break;
		}
		or _When(jobs.size() > 0) _Accept(requestWork); //accept requestWork when there are jobs on the queue
		or _Accept(create, transfer); //accept calls from students
	}
	printer.print(Printer::Kind::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	//create new card and job
	WATCard *card = new WATCard();
	Job *nextJob = new Job(Args(sid, card, amount));
	//push job onto queue
	jobs.push(nextJob);
	printer.print(Printer::Kind::WATCardOffice, 'C', sid, amount);
	return nextJob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	//create new job and push onto queue
	Job *nextJob = new Job(Args(sid, card, amount));
	printer.print(Printer::Kind::WATCardOffice, 'T', sid, amount);
	jobs.push(nextJob);
	return nextJob->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	//get job off of queue
	if (terminate) return NULL;
	Job *job = jobs.front();
	jobs.pop();
	return job;
}