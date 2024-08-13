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
