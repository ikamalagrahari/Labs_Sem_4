#!/bin/bash

is_palindrome() {
    reverse=$(echo "$1" | rev)
    if [ "$1" = "$reverse" ]; then
        echo "$1 is a palindrome."
    else
        echo "$1 is not a palindrome."
    fi
}

read -p "Enter a number to check if it's a palindrome: " num
is_palindrome "$num"
