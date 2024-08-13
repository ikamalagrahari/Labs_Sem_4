#!/bin/bash

if [ -z "$1" ]; then
    read -p "Enter a number: " num
else
    num=$1
fi

if ! [[ $num =~ ^[0-9]+$ ]]; then
    echo "Error: Not a valid number."
    exit 1
fi

if (( num % 2 == 0 )); then
    echo "$num is even."
else
    echo "$num is odd."
fi
