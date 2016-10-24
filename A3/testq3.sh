#!/bin/bash
#make clean
given=buffer
solution=q3soln
#make "$given"
#make "$solution"

for (( i=1; i <= $1; ++i ))
do
	cons=$(( ( $RANDOM % 100 ) + 1 ))
	prods=$(( ( $RANDOM % 100 ) + 1 ))
	produce=$(( ( $RANDOM % 100 ) + 1 ))
	bufferSize=$(( ( $RANDOM % 100 ) + 1 ))
	delay=$(( ( $RANDOM % 10 ) + 1 ))
	`./$given $cons $prods $produce $bufferSize $delay > first_output`
	`./$solution $cons $prods $produce $bufferSize $delay > second_output`
	echo "=================================================="
	diff first_output second_output
	echo "=================================================="
done
