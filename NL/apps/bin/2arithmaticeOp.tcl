proc add {a b} {
	set result [expr $a + $b]
	return $result
}

proc sub {a b} {
	set result [expr $a - $b]
	return $result
}

proc multiply {a b} {
	set result [expr $a * $b]
	return $result
}

proc divide {a b} {
	set result [expr $a / $b]
	return $result
}


set n1 12
set n2 15

puts "number 1 and number 2 are $n1 and $n2"
puts "Addition: [add $n1 $n2]"
puts "Subtraction: [sub $n1 $n2]"
puts "Multiply: [multiply $n1 $n2]"
puts "Division: [divide $n1 $n2]"
exit
