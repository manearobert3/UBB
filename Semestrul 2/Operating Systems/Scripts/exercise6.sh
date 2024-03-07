#!/bin/bash

while true; do
	read value
	if [ $value = "stop" ]; then
		echo "final"
		exit 0
	elif [ ! -f $value ]; then
			echo "not a file name"
	elif file $value | grep -E -q "ASCII text"; then
		echo "$value has $(cat $value | head -n 1 | wc -w)"
	fi
done
