#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <string>"
    exit 1
fi

input="$1"
uppercase=$(echo "$input" | tr '[:lower:]' '[:upper:]')
echo "Uppercase: $uppercase"
