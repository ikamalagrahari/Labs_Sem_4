# 1. Write a shell script to calculate simple interest.

read -p "Enter the principle amount: " amt 
read -p "Enter the interest rate: " rate 
read -p "Enter the time in years: " time 

echo "$((amt * rate * time / 100))"



# 2. Write a perl script to check a number is prime or not.

#!/usr/bin/perl

print "Enter a number: ";
my $number = <STDIN>;
chomp($number); # remove last next line char

# Check if the entered number is a positive integer
if ($number =~ /^[1-9]\d*$/) {
    if (is_prime($number)) {
        print "$number is a prime number.\n";
    } else {
        print "$number is not a prime number.\n";
    }
} else {
    print "Invalid input. Please enter a positive integer.\n";
}

sub is_prime {
    my $num = shift;
    return 0 if $num == 0 || $num == 1;

    for my $i (2 .. int(sqrt($num))) {
        return 0 if $num % $i == 0;  # Not a prime number if it has a factor
    }

    return 1;
}




# 3. Write a shell script to search whether element is present is in the list or not.

#!/bin/bash

list=(1 2 3 4 5 6)
read -rp "Enter the num: " num 

if [ "${list[$num]+x}" ]; then
    echo "$num exists in list!" 
else 
    echo "Not found"
fi



# 4. Write a script using sed command to replace all occurrences of particular word in given a file.

#!/bin/bash

read -rp "Enter the filename: " file
read -rp "Enter the word to replace: " word
read -rp "Enter the replacement word: " replacement

echo "Replacing all occurrences of '$word' with '$replacement' in '$file'..."
sed -i "s/$word/$replacement/g" "$file"
echo "Done."



# 5. Write a shell script to perform operations on directory like: display name of current directory; display list of directory contents; create another directory, write contents on that and copy it to a suitable location in your home directory; etc.

#!/bin/bash

echo -e """
1. Print current directory name
2. Display list of file
3. Create directory
4. Create file
5. Copy directory
"""
read -rp "Enter choice: " choice

case "$choice" in
    1) 
        echo -e "\nDirectory name: $(basename $(pwd))\n"
    ;;
    2) 
        echo -e "$(ls)\n"
    ;;
    3)
        read -rp "Enter directory name: " dir
        mkdir "$dir"
    ;;
    4) 
        read -rp "Enter filename: " file
        touch "$file"
    ;;
    5)
        read -rp "Enter directory name: " src
        read -rp "Enter destination: " dst
        cp -r "$src" "$HOME/$dst"
    ;;
    *) 
        echo "Invalid input"
    ;;
esac



# 6. Write a script using sed command to print duplicated lines in input.

#!/bin/bash

# Save input to temp file
input_file=$(mktemp)
cat > "$input_file"

sort "$input_file" | sed '$!N; s/^\(.*\)\n\1$/\1/; t; D'

rm "$input_file"

## Execution =============
# ❯ ./file.sh <<EOF
# > apple
# > grape
# > banana
# > apple
# > orange
# > grape
# > EOF



# 7. Write a Shell Script To Develop Scientific Calculator

read -p "Enter first number: " num1
read -p "Enter second number: " num2
read -p """
Select operation:
1. Addition
2. Subtraction
3. Multiplication
4. Division

> """ operation

case $operation in
1) result=$((num1 + num2))
;;
2) result=$((num1 - num2))
;;
3) result=$((num1 * num2))
;;
4) result=$((num1 / num2))
;;
*) echo "Invalid operation."
exit 1
esac

echo "Result: $result"



# 8. Write a Shell Script To Find The Given Number Is Even Or Odd

if (( $1 % 2 == 0 )); then
    echo "$1 is even."
else
    echo "$1 is odd."
fi 



# 9. Write a Shell Script To Find The Given Number Is  Palindrome or Not

is_palindrome() {
    reverse=$(echo "$1" | rev)
    if [ "$1" = "$reverse" ]; then
        echo "$1 is a palindrome."
    else
        echo "$1 is not a palindrome."
    fi
}

is_palindrome "$1"



# 10. Write a Shell Script To Generate even numbers and calculate its sum

sum_of_even() {
    local n=$1
    local sum=0
    local count=0
    local num=2
    while [ $count -lt $n ]; do
        sum=$((sum + num))
        num=$((num + 2))
        count=$((count + 1))
    done
    echo "Sum of first $n even numbers is: $sum"
}

read -p "Enter the value of n: " n_value
sum_of_even "$n_value"




# 11. Write a Shell Script To Copy A String Into Another String

copy_string() {
    local source_string=$1
    local destination_string=$2
    # Copy the source string into the destination string
    destination_string=$source_string
    echo "Source string: $source_string"
    echo "Destination string after copying:
    $destination_string"
}
# Main script
read -p "Enter the source string: " source_string
read -p "Enter the destination string: "
destination_string
copy_string "$source_string" "$destination_string"




# 12. Write a Shell Script To REVERSE THE STRING

reverse_string() {
    local input_string=$1
    local reversed_string=""
    # Loop through each character of the input string in
    reverse order
    for (( i=${#input_string}-1; i>=0; i-- )); do
        reversed_string="$reversed_string${input_string:
        $i:1}"
    done
    echo "Original string: $input_string"
    echo "Reversed string: $reversed_string"
}
# Main script
read -p "Enter a string to reverse: " input_string
reverse_string "$input_string"





# 13. Develop an interactive grep script that asks for a word and a file name and then tells how many lines contain that word. 

read -rp "Enter the name of the file: " filename

echo "Number of words character:"
cat -vet "$filename" | grep -o '\w\+\|\^M\|^\|\$' | wc -m

echo "Number of words:"
grep -o '\w\+' "$filename" | wc -w

echo "Number of lines:"
cat -vet "$filename" | grep -o '\w\+\|\^M\|^\|\$' | wc -l



# 14. Develop an interactive awk script that asks for a word and a file name and then tells how many lines contain that word.

#!/usr/bin/awk -f
BEGIN {
printf "Enter a word: "
getline word < "/dev/tty"
printf "Enter file name: "
getline filename < "/dev/tty"
close("/dev/tty")
count = 0
while ((getline line < filename) > 0) {
    if (line ~ word) {
        count.+
    }
}
close(filename)
printf "Number of lines containing '%s' in file '%s': %d\n", word, filename,
count
}


