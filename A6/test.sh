#!/bin/bash
make soda 
for (( i=1; i <= $1; ++i ))
do
	seed=$RANDOM
	`./soda soda.config $seed > output`
	echo "=================================================="
	echo "seed: $seed"
	echo "=================================================="
done
