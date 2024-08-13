reverse_string() {
    local input_string=$1
    local reversed_string=""
    # Loop through each character of the input string in reverse order
    for (( i=${#input_string}-1; i>=0; i-- )); do
        reversed_string="$reversed_string${input_string:$i:1}"
    done
    echo "Original string: $input_string"
    echo "Reversed string: $reversed_string"
}

# Main script
read -p "Enter a string to reverse: " input_string
reverse_string "$input_string"
