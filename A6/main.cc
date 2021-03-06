#include <iostream>
#include <sstream>


#include "config.h"
#include "parent.h"
#include "Student.h"
#include "rng.h"
#include "printer.h"
#include "groupoff.h"
#include "WATcard.h"
#include "BottlingPlant.h"
#include "WATcardoffice.h"
#include "VendingMachine.h"
#include "bank.h"

using namespace std;

void usage(char *argv[]) {
    cout << "Usage: " << argv[0]
     << " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );
}

void uMain::main(){
	//default parameters
	int seed = getpid();
	ConfigParms params;
	string configPath = "soda.config";
	//read command line parameters
	switch(argc){
		case 3:
			seed = atoi(argv[2]);
			if (seed < 0){
				usage(argv);
			}
			rng.set_seed((unsigned int) seed);
		case 2:
			configPath = string(argv[1]);
		case 1:
			break;
		default:
			usage(argv);
	}
	//process config
	processConfigFile(configPath.c_str(), params);

	//create objects
	Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
	Bank bank(params.numStudents);
	Groupoff groupoff(printer,params.numStudents, params.sodaCost, params.groupoffDelay);

	Parent* parent = new Parent(printer, bank, params.numStudents, params.parentalDelay);
	WATCardOffice* office = new WATCardOffice(printer, bank, params.numCouriers);
	NameServer* nameServer = new NameServer(printer, params.numVendingMachines, params.numStudents);
	VendingMachine *vendingMachine[params.numVendingMachines];
	for (unsigned int i = 0; i < params.numVendingMachines; i++){
		vendingMachine[i] = new VendingMachine(printer, *nameServer, i, params.sodaCost, params.maxStockPerFlavour);
	}

	BottlingPlant* plant = new BottlingPlant(printer, *nameServer, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);
	Student* students[params.numStudents];
	for (unsigned int i = 0; i < params.numStudents; i++){
		students[i] = new Student(printer, *nameServer, *office, groupoff, i, params.maxPurchases);
	}
	//wait for students to finish
	for (unsigned int i = 0 ; i < params.numStudents; i++){
		delete students[i];
	}
	//delete everything else
	delete plant;
	for (unsigned int i = 0 ; i < params.numVendingMachines; i++){
		delete vendingMachine[i];
	}

	delete nameServer;
	delete office;
	delete parent;
}