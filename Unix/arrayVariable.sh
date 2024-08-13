#!/usr/bin/perl

# Define an array of fruits
my @fruits = ("apple", "banana", "orange", "grape");

# Print the entire array
print "Fruits: @fruits\n";

# Accessing individual elements of the array
print "First fruit: $fruits[0]\n";
print "Second fruit: $fruits[1]\n";

# Modifying an element of the array
$fruits[2] = "strawberry";
print "Modified fruits: @fruits\n";

# Adding elements to the array
push @fruits, "kiwi";
print "After adding kiwi: @fruits\n";

# Removing elements from the array
pop @fruits;
print "After removing last element: @fruits\n";
