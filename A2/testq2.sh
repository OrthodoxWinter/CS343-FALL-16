#!/bin/bash
given=hotpotatoSoln
solution=hotpotato
make "$solution"

for (( i=1; i <= $1; ++i ))
do
	seed=$RANDOM
	numPlayers=$(( ($RANDOM % 19) + 2 ))
	`./"$given" $numPlayers $seed > first_output`
	`./"$solution" $numPlayers $seed > second_output`
	echo "=================================================="
	echo "seed: $seed"
	echo "players: $numPlayers"
	diff first_output second_output
	echo "=================================================="
done