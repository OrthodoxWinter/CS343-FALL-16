#!/bin/bash
make clean
given=resumption
solution=noresumption
make "$given"
make "$solution"

for (( i=1; i <= $1; ++i ))
do
	seed=$RANDOM
	numTimes=$(( $RANDOM % 50 ))
	`./"$given" > first_output $numTimes, $seed`
	`./"$solution" > second_output $numTimes, $seed`
	echo "=================================================="
	echo "seed: $seed"
	diff -q first_output second_output
	echo "=================================================="
done