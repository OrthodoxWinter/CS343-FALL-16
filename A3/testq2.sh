#!/bin/bash
#make clean
given=q2
solution=q2soln
#make "$given"
#make "$solution"

for (( i=1; i <= $1; ++i ))
do
	numM=$(( ( $RANDOM % 100 ) + 1 ))
	numN=$(( ( $RANDOM % 100 ) + 1 ))
	numK=$(( ( $RANDOM % 100 ) + 1 ))
	./randomMatrix $numM $numN > xfile
	./randomMatrix $numN $numK > yfile
	./q2 $numM $numN $numK xfile yfile > output1
	./q2soln $numM $numN $numK xfile yfile > output2
	echo "=================================================="
	diff output1 output2
	echo "=================================================="
done
