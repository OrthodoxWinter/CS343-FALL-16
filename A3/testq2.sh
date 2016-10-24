#!/bin/bash
#make clean
given=matrixmultiply
solution=q2soln
#make "$given"
#make "$solution"

for (( i=1; i <= $1; ++i ))
do
	numM=$(( ( $RANDOM % 10 ) + 1 ))
	numN=$(( ( $RANDOM % 10 ) + 1 ))
	numK=$(( ( $RANDOM % 10 ) + 1 ))
	./randomMatrix $numM $numN > xfile
	./randomMatrix $numN $numK > yfile
	`./$given $numM $numN $numK xfile yfile > first_output`
	`./$solution $numM $numN $numK xfile yfile > second_output`
	echo "=================================================="
	diff first_output second_output
	echo "=================================================="
done
