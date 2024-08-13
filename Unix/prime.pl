# 2. Write a perl script to check a number is prime or not.

#!/usr/bin/perl

print "Enter a number: ";
my $number = <STDIN>;
chomp($number); # remove last next line char


## Check if the entered number is a positive integer
if ($number =~ /^[1-9]\d*$/) {
    if (is_prime($number)) {
        print "$number is a prime number.\n";
    } else {
        print "$number is not a prime number.\n";
    }
} else {
    print "Invalid input. Please enter a positive integer.\n";
}

sub is_prime {
    my $num = shift;
    return 0 if $num == 0 || $num == 1;

    for my $i (2 .. int(sqrt($num))) {
        return 0 if $num % $i == 0;  # Not a prime number if it has a factor
    }

    return 1;

}
