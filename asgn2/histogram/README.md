# Histogram

## Overview
The Histogram program reads a series of positive integers from stdin and prints out a histogram with 16 bins. The program dynamically scales the bin size based on the input values, starting with a bin size of 1 and doubling it as needed to fit all positive integers observed within the histogram.

## Setup
1. Ensure you have a C compiler installed on your system.
2. Clone the repository or download the source files.
3. Navigate to the `histogram` directory.
4. Use the provided Makefile to compile the program:

## Input
Input is read from stdin, whether from the keyboard, redirected from a file, or piped in from another command. Assume the input contains only integers, separated by white space (space, tab, newline). Assume the smallest integer is zero; ignore any negative integers.

## Output
See examples provided. Note that since this program reads in from stdin until told to stop, they are not separated into inputs and outputs. Also note that "^D" (control-D) signals end of file, and is used to indicate to the program that there will be no further input.

## Exit
This program has no arguments and does not check its input for errors, so it should always exit with zero status.

## Testing
Write a short bash script that demonstrates (a) that your implementation works, and (b) that you have thoughtfully designed test cases for both normal operations and errors. Running your test script as the following will print each command as it runs (-v means verbose) and save the stdout and stderr. 

```bash
$ bash -v testing.sh >& testing.out
```

## Compilation
Provide a Makefile for your code. 

```bash
make
```

Note: Please refrain from submitting executables or .o files. They will be generated using the Makefile during the grading process.



