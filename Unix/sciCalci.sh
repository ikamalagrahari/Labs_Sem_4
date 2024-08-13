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
