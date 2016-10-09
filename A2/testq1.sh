#!/bin/bash
given=binsertsortSoln
solution=binsertsort
input=inputq1
make $solution

echo -n "" > $input

for (( i=1; i <= $1; ++i ))
do
	numValues=$(( ($RANDOM % $2) + 1 ))
	inputValues=""
	for (( j=1; j <= $numValues; ++j ))
	do
		value=$(( $RANDOM % 1000 ))
		inputValues+=" $value"
	done
	echo "$numValues$inputValues" >> $input
done
`./"$given" $input first_output`
`./"$solution" $input second_output`
echo "=================================================="
diff first_output second_output
echo "=================================================="
