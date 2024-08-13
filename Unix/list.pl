# 3. Write a shell script to search whether element is present is in the list or not.

#!/bin/bash

list=(1 2 3 4 5 6)
read -rp "Enter the num: " num 

if [ "${list[$num]+x}" ]; then
    echo "$num exists in list!" 
else 
    echo "Not found"
fi
