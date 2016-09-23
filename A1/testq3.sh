#!/bin/bash
solution=floatconstant
given=floatconstantSolution
make clean
make "$solution"
`./"$given" "$1" > first_output`
`./"$solution" "$1" > second_output`
diff first_output second_output