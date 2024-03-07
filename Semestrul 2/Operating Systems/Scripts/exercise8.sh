#!/bin/bash

while [ $# -ne 0 ]; do
	if [ -f $1 ]; then
		echo $(du -b $1)
	fi
	shift 1
done | sort -g -r  
