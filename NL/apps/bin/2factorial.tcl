proc factorial {n} {
	if {$n == 0 || $n == 1} {
		return 1
	} else { 
		return [expr $n * [factorial [expr $n - 1]]]
	}
}

set num 8
set result [factorial $num]

puts "Factorial of $num is : $result"
exit
