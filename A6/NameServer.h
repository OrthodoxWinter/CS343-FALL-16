Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	int lastPos;
	void main();
	public:
	NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine *
	vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine **	getMachineList();
	~NameServer();
};