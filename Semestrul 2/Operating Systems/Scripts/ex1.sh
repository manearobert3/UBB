#!/bin/bash

if [ $# -eq 0 ]; then
	echo "no valid username"
	exit 1
fi
while true; do
	for username in "$@"; do
		process=$(ps -u $username | wc -l)
		echo "$username: $process processes"
	done
	sleep 1
done
