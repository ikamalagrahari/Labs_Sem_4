#!/bin/bash
# 5. Write a shell script to perform operations on directory like: display name of current directory; display list of directory contents; create another directory, write contents on that and copy it to a suitable location in your home directory; etc.

echo -e "Menu:
1. Print current directory name
2. Display list of directory contents
3. Create a new directory
4. Create a new file
5. Copy directory to a new location in home directory
6. Exit"

read -rp "Enter your choice: " choice

case "$choice" in
    1)
        echo -e "\nCurrent directory: $(pwd)\n"
    ;;
    2)
        echo -e "\nDirectory contents:\n$(ls)\n"
    ;;
    3)
        read -rp "Enter directory name: " dir
        mkdir -p "$dir" && echo "Directory '$dir' created successfully."
    ;;
    4)
        read -rp "Enter filename: " file
        touch "$file" && echo "File '$file' created successfully."
    ;;
    5)
        read -rp "Enter source directory name: " src
        if [ ! -d "$src" ]; then
            echo "Source directory '$src' does not exist."
        else
            read -rp "Enter destination directory name in home directory: " dst
            cp -r "$src" "$HOME/$dst" && echo "Directory '$src' copied to '$HOME/$dst' successfully."
        fi
    ;;
    6)
        echo "Exiting..."
        exit 0
    ;;
    *)
        echo "Invalid input. Please enter a number from the menu."
    ;;
esac

