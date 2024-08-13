# Function to calculate Fibonacci sequence
proc fibonacci {n} {
    set fib_sequence [list 0 1]
    while {[llength $fib_sequence] < $n} {
        set next_number [expr {[lindex $fib_sequence end] + [lindex $fib_sequence end-1]}]
        lappend fib_sequence $next_number
    }
    return [lrange $fib_sequence 0 [expr {$n-1}]]
}

# Example: Print the first 10 Fibonacci numbers
puts [fibonacci 10]