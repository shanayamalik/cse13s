# Coolness

## Overview

The C program is designed to compute the "coolness" factor based on given temperature and wind speed values. The formula and constraints for the calculation are defined within the program.

## Features

- **Flexible Input**: The program accepts zero, one, or two command line arguments, allowing users to specify temperature and/or wind speed.
- **Error Handling**: Comprehensive error messages guide the user for incorrect inputs or usage.
- **Range Calculations**: When no arguments are provided, the program computes coolness for a predefined range of temperature and wind speed values.
- **Precision Output**: Results are displayed with precision up to the tens place, ensuring accurate readings.
- **Testing Script**: A bash script (`testing.sh`) is included to demonstrate the program's functionality and robustness.

## Usage

```bash
./coolness               
./coolness [temperature] 
./coolness [temperature] [wind speed]
```

## Compilation

To compile the program, utilize the provided Makefile:

```bash
make
```

Note: The C math library is required for compilation. Ensure that #include <math.h> is present in coolness.c and -lm is added to the gcc command in the Makefile.

## Testing
To validate the program's functionality, run the provided testing script:

```bash
bash -v testing.sh >& testing.out
```

This command will execute the tests, display each command as it runs, and save the results to testing.out.

## Directory Structure
The project directory includes the following files:
```bash
asgn2
|-- coolness
|   |-- .gitignore
|   |-- coolness.c
|   |-- testing.out
|   |-- testing.sh
|   |-- Makefile
|   |-- README.md
|-- histogram
```

Note: Please refrain from submitting executables or .o files. They will be generated using the Makefile during the grading process.
