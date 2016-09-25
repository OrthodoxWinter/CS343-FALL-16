#!/bin/bash
make clean
given=resumption
solution=noresumption
make "$given"
make "$solution"

for (( i=1; i <= $1; ++i ))
do
	seed=$RANDOM
	numTimes=$(( $RANDOM % 100 ))
	`./"$given" $numTimes, $seed > first_output`
	`./"$solution" $numTimes, $seed > second_output`
	echo "=================================================="
	echo "seed: $seed"
	diff -q first_output second_output
	echo "=================================================="
done