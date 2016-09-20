#!/bin/bash
make clean
given=longjmp
solution=throwcatch
make "$given"
make "$solution"

for (( i=1; i <= $1; ++i ))
do
	seed=$RANDOM
	numM=$(( $RANDOM % 30 ))
	numN=$(( $RANDOM % 30 ))
	`./"$given" > first_output $numM, $numN, $seed`
	`./"$solution" > second_output $numM, $numN, $seed`
	echo "=================================================="
	echo "seed: $seed"
	diff -q first_output second_output
	echo "=================================================="
done