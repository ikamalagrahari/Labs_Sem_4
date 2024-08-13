proc printPyramid {rows} {
    for {set i 1} {$i <= $rows} {incr i} {
        for {set j 1} {$j <= $rows-$i} {incr j} {
            puts -nonewline " "
        }

        for {set k 1} {$k <= $i} {incr k} {
            puts -nonewline "* "
        }

        puts ""
    }
}

set numberOfRows 5
printPyramid $numberOfRows
