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
