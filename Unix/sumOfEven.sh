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
