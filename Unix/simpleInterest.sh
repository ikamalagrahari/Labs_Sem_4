# 1. Write a shell script to calculate simple interest.

read -p "Enter the principle amount: " amt 
read -p "Enter the interest rate: " rate 
read -p "Enter the time in years: " time 

echo "$((amt * rate * time / 100))"
