CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -std=c++11
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o BottlingPlant.o config.o VendingMachine.o NameServer.o Truck.o Student.o printer.o groupoff.o WATcard.o WATcardoffice.o parent.o bank.o  rng.o
EXEC = soda

.PHONY : clean

#############################################################
${EXEC} : ${OBJECTS}				# link step 2nd executable
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
