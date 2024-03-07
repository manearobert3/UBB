#!/bin/bash
if [ $# -lt 2 ]; then
	echo "input 2 args"
	exit 0
fi

if [ $(($# % 2)) -eq 1 ]; then
	echo "input pairs plox"
	exit 1
fi

while [ $# -ge 2 ]; do
	file=$1
	word=$2
	count=$(cat $file | grep -E -o "\<$word\>" | wc -l)
	echo $count
	shift 2
done
