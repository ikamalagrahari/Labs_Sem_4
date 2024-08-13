# 13. Develop an interactive grep script that asks for a word and a file name and then tells how many lines contain that word. 

read -rp "Enter the name of the file: " filename

echo "Number of words character:"
cat -vet "$filename" | grep -o '\w\+\|\^M\|^\|\$' | wc -m

echo "Number of words:"
grep -o '\w\+' "$filename" | wc -w

echo "Number of lines:"
cat -vet "$filename" | grep -o '\w\+\|\^M\|^\|\$' | wc -lecho "Enter a word"
read word
echo "Enter filename"
read file

nol=$(grep -c "$word" "$file")
echo "$nol times '$word' present in '$file"'
