#!/bin/sh
for i in "hello 1 * 2 goodbye" 
do
       	echo "Looping ... number $i"
done
variable=hello
while [ ! -f $variable ]
do
	echo "input something:"
	read variable
	echo "you typed $variable"
	echo "you typed ${variable}"
	if [ -f $variable ]; then
		echo "you introduced a file"
	elif [ -d $variable ]; then
		echo "you introduced a directory"
	elif echo $variable | grep -E -q "^[0-9]+$"; then
		echo "you introduced number"
	fi
done
