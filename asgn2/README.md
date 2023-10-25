# Assignment 2: CSE 13S (C Programming)

## Overview

This assignment encompasses two primary programs: one that computes the "coolness" factor based on given temperature and wind speed values, and another that reads positive integers from stdin to print a histogram with 16 bins. The histogram program dynamically scales the bin size based on input values.

## Features

- **Flexible Input**: Both programs are designed to accept varying input formats and provide comprehensive error messages for incorrect usage.
- **Dynamic Scaling**: The histogram program adjusts the bin size dynamically, starting at 1 and doubling as needed.
- **Precision & Accuracy**: The coolness program displays results with precision up to the tens place.
- **Testing Script**: A bash script (`testing.sh`) is included for both programs to demonstrate functionality and robustness.

## Usage

For the coolness program:
```bash
./coolness               
./coolness [temperature] 
./coolness [temperature] [wind speed]
```

For the histogram program, input is read from stdin. The program assumes only integers separated by white space. The smallest integer is zero, and negative integers are ignored.

## Compilation

Both programs can be compiled using their respective provided Makefiles:

```bash
./coolness               
./coolness [temperature] 
./coolness [temperature] [wind speed]
```
Note: Ensure any necessary libraries or headers are included in the source files and Makefiles.

## Testing
To validate the functionality of both programs, run the provided testing script:

```bash
bash -v testing.sh >& testing.out
```

Note: Please refrain from submitting executables or .o files. They will be generated using the Makefile during the grading process.
