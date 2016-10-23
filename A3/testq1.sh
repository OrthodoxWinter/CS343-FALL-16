#!/bin/bash
#make clean
given=q1soln
solution=q1
#make "$given"
#make "$solution"

for (( i=1; i <= $1; ++i ))
do
	time=$(( $RANDOM % 20 ))
        L1=$(( $RANDOM % 5 ))
        L2=$(( $RANDOM % 5 ))
        L3=$(( $RANDOM % 5 ))
	`./"$given" $time $L1 $L2 $L3 > first_output`
	`./"$solution" $time $L1 $L2 $L3 > second_output`
	echo "=================================================="
        echo "time: $time L1: $L1 L2: $L2 L3: $L3"
	diff first_output second_output
	echo "=================================================="
done
