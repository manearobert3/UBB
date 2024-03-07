#!/bin/bash

if [ $# -eq 0 ]; then
	echo "no args"
	exit 1
fi

for (( i=1; i<=$#; i=i+2)); do
	name=$i
	echo $i
	i=i-1
	searchstring=$i
	i=i+1
	echo $i
	echo name
	echo searchstring
done

