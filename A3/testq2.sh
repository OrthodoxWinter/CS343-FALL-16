#!/bin/bash
given=matrixmultiply
solution=matrixmultiplySoln
make "$given"

for (( i=1; i <= $1; ++i ))
do
	numM=$(( ( $RANDOM % 100 ) + 1 ))
	numN=$(( ( $RANDOM % 100 ) + 1 ))
	numK=$(( ( $RANDOM % 100 ) + 1 ))
	./randomMatrix $numM $numN > xfile
	./randomMatrix $numN $numK > yfile
	`./$given $numM $numN $numK xfile yfile > first_output`
	`./$solution $numM $numN $numK xfile yfile > second_output`
	echo "=================================================="
	diff first_output second_output
	echo "=================================================="
done
