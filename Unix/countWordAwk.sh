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
