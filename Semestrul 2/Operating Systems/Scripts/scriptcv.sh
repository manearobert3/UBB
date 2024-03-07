#!/bin/bash

# Loop through each argument
for num in "$@"; do
	    # Check if the argument is a number
	        if [[ "$num" =~ ^[0-9]+$ ]]; then
			        # Check if the number is even
				        if (( num % 2 == 0 )); then
						            echo "$num is even"
							            fi
								        fi
								done
